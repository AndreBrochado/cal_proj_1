/*
 * Ride.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDE_H_
#define SRC_RIDE_H_

#include <ctime>
#include <memory>
#include "RoadMap.h"
#include "User.h"

const double velAvr = 50000/3600; //50km/h in m/s

class Ride {
protected:
	//Como saber o tempo dispendido
	uint departurePlace, arrivalPlace;
	time_t departureTime, estimatedArrival, departureTolerance, arrivalTolerance;
	int noSeats;
	User* driver;
	vector<User*> hitchhikers;
public:
	Ride(){};
	Ride(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
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
