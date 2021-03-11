//
//  main.cpp
//  MovieTheaterSeatingChallenge
//
//  Created by Samuel Donovan on 2/17/21.
//

#include "Utilities.h"
#include <fstream>

using namespace std;

// returns a) the RDListIteratorList of RD's we'll use to populate these seats
//         b) the number of seats used
pair<RDListIteratorList,int> maximizeSeatsUsed(RDList::iterator begin, RDList::iterator const end, int seatBound) {
    
    RDListIteratorList bestIteratorList;
    
    if (seatBound < 1) return pair<RDListIteratorList,int>(bestIteratorList,0);
    
    // advance until begin == end || begin->size <= seatBound
    while (true) {
        if (begin == end) return pair<RDListIteratorList,int>(bestIteratorList,0);
        if (begin->size == seatBound) {
            bestIteratorList.push_back(begin);
            return pair<RDListIteratorList,int>(bestIteratorList,seatBound);
        }
        if (begin->size < seatBound) break;
        ++begin;
    }
    
    RDList::iterator currentHead = begin;
    int bestSeatCount;
    
    ++begin;
    pair<RDListIteratorList,int> bestFinder = maximizeSeatsUsed(begin, end, seatBound - currentHead->size - 3);
    bestSeatCount = currentHead->size + bestFinder.second;
    bestIteratorList = bestFinder.first;
    
    // now search the rest of the list for better
    while (begin != end) {
        RDList::iterator potentialCurrentHead = begin;
        ++begin;
        
        bestFinder = maximizeSeatsUsed(begin, end, seatBound - currentHead->size - 3);
        const int potentialBestSeatBound = potentialCurrentHead->size + bestFinder.second;
        
        if (bestSeatCount < potentialBestSeatBound) {
            // we have a new best
            bestSeatCount = potentialBestSeatBound;
            currentHead = potentialCurrentHead;
            bestIteratorList = bestFinder.first;
        }
        
        // there should be some special case to break if we have a node that has already been encountered in one of our bestFinder lists
        // we should also skip over checking 3 or more of same value in a row (eg, 3->3->3->3 can start skipping after first (3,3))
    }
    
    bestIteratorList.push_front(currentHead);
    return pair<RDListIteratorList,int>(bestIteratorList,bestSeatCount);
    
}

bool compareReservationSize(ReservationData lhs, ReservationData rhs) {
    return lhs.size > rhs.size;
}

bool compareReservationID(ReservationData lhs, ReservationData rhs) {
    return lhs.id < rhs.id;
}

vector<ReservationData> getFirstSeats(RDList & reservations) {
    
    // sort reservationData
    reservations.sort(compareReservationSize);
    
    vector<ReservationData> rd;
    
    for (char currentRow = 'A'; currentRow < 'A' + numRows; currentRow+=2) {
        // put as many customers as possible in this row
        pair<RDListIteratorList,int> results = maximizeSeatsUsed(reservations.begin(), reservations.end(), numSeats);
        
        // push customers to the middle
        int seat = 0 + (20 - results.second - 3*(results.first.size()-1))/2;
        // end push customers to the middle
        
        for (RDList::iterator const & rdli : results.first) {
            rdli->col = seat;
            rdli->row = currentRow;
            seat += rdli->size;
            seat += 3;
            rd.push_back(*rdli);
            reservations.erase(rdli);
        }
    }
        
    return rd;
}

int main(int argc, const char * argv[]) {
    
    string filename;
    cin >> filename;
    
    ifstream inputFile(filename);
    
    RDList reservations = parse(inputFile);
    
    inputFile.close();
    
    // cout << "Done parsing...assigning reservations" << endl;
    
    vector<ReservationData> rd = getFirstSeats(reservations);
    // cout << "Done assigning reservations...starting printing" << endl;
    
    sort(rd.begin(), rd.end(), compareReservationID);
    
    const char* outputFileName = "output.txt";
    
    ofstream outputFile(outputFileName);
    
    print(outputFile, rd);
    // cout << "Done printing...exiting" << endl;
    
    outputFile.close();
    
    cout << outputFileName << endl;
    
    return 0;
}
