/*
 * RideRequest.h
 *
 *  Created on: 20/04/2016
 *      Author: In�s
 */

#ifndef SRC_RIDEREQUEST_H_
#define SRC_RIDEREQUEST_H_

#include "Ride.h"

class RideRequest: public Ride {
private:

public:
	RideRequest(unsigned int arrivalPlace, unsigned int departurePlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
	virtual ~RideRequest();
};

#endif /* SRC_RIDEREQUEST_H_ */
