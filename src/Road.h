/*
 * Road.h
 *
 *  Created on: 16/04/2016
 *      Author: Inês
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Crossroad.h"

class Road{
private:
	string name;
	bool twoWay;
	vector<Crossroad*> crossroads;
public:
	Road(string name, bool twoWay): name(name), twoWay(twoWay){} ///< Constructor

	const string& getName() const {
		return name;
	}

	bool isTwoWay() const {
		return twoWay;
	}

	void addCrossroad(Crossroad* c){
		crossroads.push_back(c);
	}
};


#endif /* SRC_ROAD_H_ */
