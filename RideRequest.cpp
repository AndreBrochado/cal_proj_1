/*
 * RideRequest.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideRequest.h"

RideRequest::RideRequest(unsigned int arrivalPlace, unsigned int departurePlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats):
Ride(arrivalPlace, departurePlace, departureTime, departureTolerance, arrivalTolerance, noSeats){

}

RideRequest::~RideRequest() {
	// TODO Auto-generated destructor stub
}

