//
//  Utilities.h
//  MovieTheaterSeatingChallenge
//
//  Created by Samuel Donovan on 2/17/21.
//

#ifndef Utilities_h
#define Utilities_h

#include <iostream>
#include <utility>
#include <list>
#include <vector>

const int numRows = 10;
const int numSeats = 20;

struct ReservationData {
    std::string id;
    int size;
    
    char row = 0;
    int col = 0;
    
    ReservationData(std::string id, int size) :
    id(id), size(size) {}
};

typedef std::list<ReservationData> RDList;
typedef std::list<RDList::iterator> RDListIteratorList;

RDList parse(std::istream & input);

void print(std::ostream & input, std::vector<ReservationData> const & rd);

#endif /* Utilities_h */
