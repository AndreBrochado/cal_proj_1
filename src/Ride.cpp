/*
 * Ride.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Inês
 */

#include "Ride.h"

Ride::Ride(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats):
	departureTime(departureTime), estimatedArrival(estimatedArrival), departureTolerance(departureTolerance), arrivalTolerance(arrivalTolerance), noSeats(noSeats){

}

Ride::~Ride() {
	// TODO Auto-generated destructor stub
}

