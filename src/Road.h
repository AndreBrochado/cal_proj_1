/*
 * Road.h
 *
 *  Created on: 16/04/2016
 *      Author: Ines
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Crossroad.h"
#include <windows.h>

class Road{
private:
	string name;
	bool twoWay;
	vector<double> aproximateDoorNumbers;
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
		if(crossroads.empty()){
			aproximateDoorNumbers.push_back(0);
			crossroads.push_back(c);
		}
		else if(crossroads.back()->getId() != c->getId()){
			aproximateDoorNumbers.push_back(aproximateDoorNumbers.back() + crossroads.back()->getDist(*c));
			crossroads.push_back(c);
		}
	}

	vector<Crossroad*> getCrossroads(){
		return crossroads;
	}

	unsigned int getNodeId(string roadName, double doorNumber){
		if(roadName != name)
			return -1;

		unsigned int id =crossroads.front()->getId();
		double dist = doorNumber;

		for (int i = 0; i < aproximateDoorNumbers.size(); ++i) {
			double dist_tmp = abs(doorNumber - aproximateDoorNumbers[i]);
			if(dist_tmp < dist){
				dist = dist_tmp;
				id = crossroads[i]->getId();
			}
		}

		return id;
	}
};


#endif /* SRC_ROAD_H_ */
