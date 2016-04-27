/*
 * Ride.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "Ride.h"

Ride::Ride(unsigned int arrivalPlace, unsigned int departurePlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats):
arrivalPlace(arrivalPlace), departurePlace(departurePlace), departureTime(departureTime), departureTolerance(departureTolerance), arrivalTolerance(arrivalTolerance), noSeats(noSeats){

}

Ride::~Ride() {
	// TODO Auto-generated destructor stub
}

