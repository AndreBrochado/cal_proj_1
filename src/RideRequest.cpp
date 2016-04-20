/*
 * RideRequest.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Inês
 */

#include "RideRequest.h"

RideRequest::RideRequest(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* hitchhiker):
	Ride(departureTime, estimatedArrival, departureTolerance, arrivalTolerance, noSeats), hitchhiker(hitchhiker){

}

RideRequest::~RideRequest() {
	// TODO Auto-generated destructor stub
}

