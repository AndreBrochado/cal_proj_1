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

class RideCompleted{
	RideOffer* rideOffer;
	std::vector<RideRequest*> rideRequest;
public:
	RideCompleted(RideOffer* rideOffer);
	virtual ~RideCompleted();
};

#endif /* SRC_RIDECOMPLETED_H_ */
