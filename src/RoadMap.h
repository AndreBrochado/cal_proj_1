/*
 * Map.h
 *
 *  Created on: 16/04/2016
 *      Author: Inês
 */

#ifndef MAP_H_
#define MAP_H_

#include "Graph.h"
#include "Road.h"
#include "Crossroad.h"
#include "GraphViewer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>

typedef unsigned int uint;

class Road;

/**
* Represents an RoadMap
*/
class RoadMap : protected Graph<Crossroad>
{
private:
	map<uint, Crossroad> crossRoads;
	map<uint, Road> roads;

	float latitude_min;
	float longitude_min;
	float longitude_max;
	float latitude_max;

	void readNodesFile(const std::string& fnodes);
	void readRoadsFile(const std::string& froads);
	void readSubRoadsFile(const std::string& fsubroads);

	GraphViewer *gv;
public:
    RoadMap(const std::string& fnodes, const std::string& froads, const std::string& fsubroads); ///< Constructor
    void viewMap();
    void bestPath(uint id_src, uint id_dest, list<uint>mustPass);
    void bestPath(uint id_src, uint id_dest, list<uint>mustPass, vector<Crossroad> &path);
    ~RoadMap(); ///< Destructor
};

#endif /* SRC_MAP_H_ */
