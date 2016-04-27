/*
 * Map.h
 *
 *  Created on: 16/04/2016
 *      Author: Ines
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
 * @class RoadMap represents a Road Map
 */
class RoadMap : protected Graph<Crossroad> {
private:
    map<uint, Crossroad> crossRoads;
    map<uint, Road> roads;

    float latitude_min;
    float longitude_min;
    float longitude_max;
    float latitude_max;

    /**
     * Reads nodes file
     */
    void readNodesFile(const std::string &fnodes);

    /**
     * Reads roads file
     */
    void readRoadsFile(const std::string &froads);

    /**
     * Reads subRoads file
     */
    void readSubRoadsFile(const std::string &fsubroads);

    GraphViewer *gv;
    static bool instanceFlag;
    static RoadMap *rm;

    /**
     * Class base constructor
     */
    RoadMap(const std::string &fnodes, const std::string &froads, const std::string &fsubroads);
public:

    /**
     * Shows the map on the screen
     */
    void viewMap();

    bool bestPath(uint newSrc, uint newDest, list<uint> &oldPath, list<double> &dist);

    bool insertNewDest(uint id_src, uint id_dest, list<uint> mustPass, list<uint> &path, list<double> &dist);

    void insertNewSrc(uint srcId, uint destId, uint newSrc, list<uint> &mustPass, list<uint> &path, list<double> &dist);

    uint getCrossroadIdFromAddress(string roadName, double doorNumber);

    double getDist(uint srcId, uint destId);

    void visualizePath(list<uint> path);

    static RoadMap *getInstance();

    ~RoadMap(); ///< Destructor
};

#endif /* SRC_MAP_H_ */
