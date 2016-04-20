/*
 * RideOffer.h
 *
 *  Created on: 20/04/2016
 *      Author: Inês
 */

#ifndef SRC_RIDEOFFER_H_
#define SRC_RIDEOFFER_H_

#include "Ride.h"

class RideOffer: public Ride {
private:
	User* driver;
public:
	RideOffer(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver);
	virtual ~RideOffer();
};

#endif /* SRC_RIDEOFFER_H_ */
