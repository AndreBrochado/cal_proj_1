/*
 * Map.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Ines
 */

#include "RoadMap.h"


void RoadMap::readNodesFile(const std::string& fnodes){
	std::ifstream nodes;
	string str;
	stringstream ss;

	nodes.open(fnodes.c_str());
	if(!nodes.is_open()){
		std::cout << "Nodes file does not exist\n";
		return;
	}

	while(!nodes.eof()){
		uint id;
		float lat_d, lat_r;
		float lon_d, lon_r;
		char lixo;

		ss.clear();
		getline(nodes, str, '\n');
		ss << str;
		ss >> id >> lixo >> lat_d >> lixo >> lon_d >> lixo >> lon_r >> lixo >> lat_r;

		if(lat_d < latitude_min)
			latitude_min = lat_d;
		if(lat_d > latitude_max)
			latitude_max = lat_d;

		if(lon_d < longitude_min)
			longitude_min = lon_d;
		if(lon_d > longitude_max)
			longitude_max = lon_d;

		Crossroad c(id, lat_d, lon_d, lon_r, lat_r);

		crossRoads.insert(std::pair<uint,Crossroad>(id, c));

		this->addVertex(c);

	}
	nodes.close();
}

void RoadMap::readRoadsFile(const std::string& froads){
	std::ifstream roads;
	string str;
	stringstream ss;

	roads.open(froads.c_str());

	while(!roads.eof()){
		uint id;
		string name;
		bool isTwoWay;

		getline(roads, str, ';');
		ss.clear();
		ss << str;
		ss >> id;

		getline(roads, name, ';');
		getline(roads, str, '\n');

		if(str == "True")
			isTwoWay = true;
		else
			isTwoWay = false;

		Road r(name, isTwoWay);
		this->roads.insert(std::pair<uint,Road>(id, r));
	}
	roads.close();
}

void RoadMap::readSubRoadsFile(const std::string& fsubroads){
	std::ifstream subroads;
	int i = 0;

	subroads.open(fsubroads.c_str());
	if(!subroads.is_open()){
		std::cout << "subroads file does not exist\n";
		return;
	}
	while(!subroads.eof()){
		string str;
		stringstream ss;
		uint id_road, id_node1, id_node2;
		char lixo;

		ss.clear();
		getline(subroads, str, '\n');
		ss << str;
		ss >> id_road >> lixo >> id_node1 >> lixo >> id_node2;

		//TODO Falta conferir se os id est�o em crossroads/roads.
		Crossroad* c1 = &crossRoads.find(id_node1)->second;
		Crossroad* c2 = &crossRoads.find(id_node2)->second;
		Road* r = &roads.find(id_road)->second;
		r->addCrossroad(c1);
		r->addCrossroad(c2);

		uint dist = c1->getDist(*c2);

		if(!this->addEdge(*c1, *c2, dist))
			cerr << "Edge ups..." << id_node1 << " " << id_node2 << endl;

		if(r->isTwoWay()){
			if(!this->addEdge(*c2, *c1, dist))
				cerr << "Edge ups..." << id_node2 << " " << id_node1 << endl;
			i++;
		}
		i++;
	}
	subroads.close();

	cout << i;
}

RoadMap::RoadMap(const std::string& fnodes, const std::string& froads, const std::string& fsubroads){

	latitude_min = 180;
	longitude_min = 180;
	longitude_max = -180;
	latitude_max = -180;

	readNodesFile(fnodes);
	cout << this->crossRoads.size() << " nodes loaded" << endl;
	readRoadsFile(froads);
	cout << this->roads.size() << " roads loaded" << endl;
	readSubRoadsFile(fsubroads);
	cout << " edges loaded" << endl;

	//floydWarshallShortestPath();

	cout << "latitude_min: " << latitude_min << endl;
	cout << "latitude_max: " << latitude_max << endl;
	cout << "longitude_min: " << longitude_min << endl;
	cout << "longitude_max: " << longitude_max << endl;

}

void RoadMap::viewMap(){
	//	uint width = 800;
	//	uint height = 1113;
	uint width = 1360;
	uint height = 1300;

	gv = new GraphViewer(width, height, false);

	//Colocar a imagem �background.jpg� como fundo
	gv->setBackground("background.jpg");

	gv->createWindow(width, height);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->defineEdgeCurved(false);

	{
		vector<Vertex<Crossroad> *>::iterator it = vertexSet.begin();
		vector<Vertex<Crossroad> *>::iterator ite = vertexSet.end();

		while(it != ite){
			gv->addNode((*it)->getInfo().getId(),width*((*it)->getInfo().getLongitudeInDegrees()-longitude_min)/(longitude_max-longitude_min) ,height - (height*((*it)->getInfo().getLatitudeInDegrees()-latitude_min)/(latitude_max-latitude_min)));
			gv->setVertexSize((*it)->getInfo().getId(), 5);
			gv->setVertexLabel((*it)->getInfo().getId(), ".");
			it++;
		}
	}

	{
		vector<Vertex<Crossroad> *>::iterator it = vertexSet.begin();
		vector<Vertex<Crossroad> *>::iterator ite = vertexSet.end();
		int id = 0;

		while(it != ite){
			vector<Edge<Crossroad> > edge = (*it)->getAdj();
			for (unsigned int i = 0; i < (*it)->getAdj().size(); ++i) {
				gv->addEdge(id, (*it)->getInfo().getId(), edge[i].getDest()->getInfo().getId(), EdgeType::DIRECTED);
				id++;
			}
			it++;
		}
	}

	gv->rearrange();
}

//TODO: GET BETTER NAME FOR THIS FUNC
void RoadMap::setNextPoint(list<uint>::iterator startPoint, list<uint>::iterator lastEl, list<uint>& oldPath){

	double min = 1000000;
	list<uint>::iterator aux, bestNextPoint;

	if(startPoint == lastEl)
		return;

	for(list<uint>::iterator it = startPoint; it != lastEl;){
		Crossroad tmp = crossRoads.find(*it)->second;
		cout << "-> "<< tmp.getId() << endl;
		dijkstraShortestPath(tmp);
		for(aux = it++; aux != lastEl; aux++){
			Crossroad temp = crossRoads.find(*aux)->second;
			if(getVertex(temp)->getDist() < min) {
				min = getVertex(temp)->getDist();
				bestNextPoint = aux;
			}
		}
	}

	oldPath.insert(startPoint, *bestNextPoint);
	oldPath.erase(bestNextPoint);
}

bool RoadMap::bestPath(uint newSrc, uint newDest, list<uint> &oldPath){
	Crossroad src = crossRoads.find(newSrc)->second;

	list<uint>::iterator it, lastEl, bestDeviation;
	lastEl = oldPath.end();
	lastEl--;

	double min = INT_MAX;

	for(it = oldPath.begin(); it != lastEl; it++){
		Crossroad tmp = crossRoads.find(*it)->second;
		dijkstraShortestPath(tmp);
		if(getVertex(src)->getDist() < min) {
			min = getVertex(src)->getDist();
			bestDeviation = it;
		}
	}

	bestDeviation++;
	oldPath.insert(bestDeviation, newSrc);

	bestDeviation--;

	min = INT_MAX;

	for(it = bestDeviation; it != lastEl; it++){
		Crossroad tmp = crossRoads.find(*it)->second;
		dijkstraShortestPath(tmp);
		if(getVertex(src)->getDist() < min) {
			min = getVertex(src)->getDist();
			bestDeviation = it;
		}
	}

	bestDeviation++;

	if(newDest != *lastEl){
		oldPath.insert(bestDeviation, newDest);
	}

	//TODO: validate new path (time and tolerances)
	return true;

}

uint RoadMap::getCrossroadIdFromAddress(string roadName, double doorNumber){
	uint id = -1;

	for (map<uint, Road>::iterator it = roads.begin(); it != roads.end() && id == -1; it++) {
		id = it->second.getNodeId(roadName, doorNumber);
	}

	return id;
}

void RoadMap::visualizePath(const list<uint> &path){

	uint stopNo = 1;
	list<uint>::const_iterator it = path.begin();
	list<uint>::const_iterator ite = path.end();

	Crossroad c = crossRoads.find(*it)->second;
	dijkstraShortestPath(c);

	//Set path source orange
	gv->setVertexColor(*it, "orange");
	gv->setVertexSize(*it, 20);

	it++;

	while(it != ite){
		Sleep(1000);

		dijkstraShortestPath(c);

		Crossroad tmp = crossRoads.find(*it)->second;
		vector<Crossroad> subPath = getPath(c, tmp);
		stringstream ss;
		
		ss << "Paragem " << stopNo;

		for (uint i = 1; i < subPath.size()-1; ++i) {
			gv->setVertexColor(subPath[i].getId(), "yellow");
			gv->setVertexSize(subPath[i].getId(), 10);
		}

		cout << c.getId() << " " << tmp.getId() << " = " << *it <<endl;

		gv->setVertexColor(*it, "pink");
		gv->setVertexSize(*it, 20);
		gv->setVertexLabel(*it, ss.str());

		gv->rearrange();
		c=tmp;

		stopNo++;
		it++;
	}

	//Set path destination red
	it--;
	gv->setVertexColor(*it, "red");
	gv->setVertexLabel(*it, "Destino");

	gv->rearrange();
}

RoadMap::~RoadMap(){}


