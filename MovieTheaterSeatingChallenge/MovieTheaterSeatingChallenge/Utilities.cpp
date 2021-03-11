//
//  IOUtilities.cpp
//  MovieTheaterSeatingChallenge
//
//  Created by Samuel Donovan on 2/17/21.
//

#include "Utilities.h"

using namespace std;

RDList parse(istream & input) {
    RDList reservations;
    
    string id;
    int size;
    
    while (true) {
        if (!(input >> id)) break;
        if (!(input >> size)) {
            cout << "Couldn't read size...skipping" << endl; continue;
        }
        if (size > 20) {
            // could handle this case by breaking them up into groups...
            // ReservationData becomes "seat chunks"
            cout << "Cannot fit all these people in one row...skipping" << endl;
            continue;
        } else if (size < 1) {
            cout << "Less than one person in this row...skipping" << endl;
            continue;
        }
        reservations.push_back(ReservationData(id,size));
    }
    
    return reservations;
}

void print(ostream & output, vector<ReservationData> const & rd) {
    for (ReservationData const & reservationData : rd) {
        output << reservationData.id << ' ';
        for (int i = 1; i <= reservationData.size; i++) {
            output << reservationData.row << reservationData.col + i;
            if (i != reservationData.size) output << ',';
            else output << endl;
        }
    }
}
