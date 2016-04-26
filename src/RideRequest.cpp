/*
 * RideRequest.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideRequest.h"

RideRequest::RideRequest(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats):
	Ride(departureTime, estimatedArrival, departureTolerance, arrivalTolerance, noSeats){

}

RideRequest::~RideRequest() {
	// TODO Auto-generated destructor stub
}

