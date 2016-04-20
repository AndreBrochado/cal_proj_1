/*
 * Ride.h
 *
 *  Created on: 20/04/2016
 *      Author: Inês
 */

#ifndef SRC_RIDE_H_
#define SRC_RIDE_H_

#include <ctime>
#include <memory>
#include "User.h"

class Ride {
protected:
	//Como saber o tempo dispendido
	//TODO: T arrivalPlace, departurePlace
	time_t departureTime, estimatedArrival, departureTolerance, arrivalTolerance;
	int noSeats;
public:
	Ride(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
	virtual ~Ride();

	time_t getArrivalTolerance() const {
		return arrivalTolerance;
	}

	time_t getDepartureTime() const {
		return departureTime;
	}

	time_t getDepartureTolerance() const {
		return departureTolerance;
	}

	time_t getEstimatedArrival() const {
		return estimatedArrival;
	}

	int getNoSeats() const {
		return noSeats;
	}
};

#endif /* SRC_RIDE_H_ */
