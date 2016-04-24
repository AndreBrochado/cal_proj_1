/*
 * RideCompleted.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDECOMPLETED_H_
#define SRC_RIDECOMPLETED_H_

#include "RideOffer.h"
#include "RideRequest.h"
#include <vector>

class RideCompleted: public Ride {
	RideOffer* rideOffer;
	std::vector<RideRequest*> rideRequest;
public:
	RideCompleted(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats, RideOffer* rideOffer);
	virtual ~RideCompleted();
};

#endif /* SRC_RIDECOMPLETED_H_ */
