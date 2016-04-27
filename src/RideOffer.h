/*
 * RideOffer.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDEOFFER_H_
#define SRC_RIDEOFFER_H_

#include "Ride.h"
#include "Crossroad.h"
#include "Graph.h"
#include <list>

class RideOffer: public Ride {
private:
	std::list<unsigned int> route;
public:
	RideOffer(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver);
	virtual ~RideOffer();
};

#endif /* SRC_RIDEOFFER_H_ */
