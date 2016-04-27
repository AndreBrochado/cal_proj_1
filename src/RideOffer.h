/*
 * RideOffer.h
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#ifndef SRC_RIDEOFFER_H_
#define SRC_RIDEOFFER_H_

#include "Ride.h"
#include "RideRequest.h"
#include "Crossroad.h"
#include "Graph.h"
#include <list>

/**
 * @class RideOffer holds information of ride offers
 */
class RideOffer : public Ride {
private:
    std::list<unsigned int> route;
    vector<RideRequest> requests;
public:
    /**
     * Class base constructor
     */
    RideOffer(uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance,
              time_t arrivalTolerance, int noSeats, User *driver);

    /**
     * Class default destructor
     */
    virtual ~RideOffer();

    /**
     * @returns associated requests
     */
    const vector<RideRequest> &getRequests() const {
        return requests;
    }

    /**
     * @returns the current route
     */
    const std::list<unsigned int> &getRoute() const {
        return route;
    }

    /**
     * Sets the route to a given path
     * @param route given route to set
     */
    void setRoute(const std::list<unsigned int> &route) {
        this->route = route;
    }

    /**
     * Adds a request to the requests vector
     */
    void addRequest(RideRequest request) {
        this->noSeats -= request.getNoSeats();
        requests.push_back(request);
    }
};

#endif /* SRC_RIDEOFFER_H_ */
