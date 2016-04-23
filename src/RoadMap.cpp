/*
 * Map.cpp
 *
 *  Created on: 16/04/2016
 *      Author: Inês
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

		//TODO Falta conferir se os id estão em crossroads/roads.
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
	uint width = 345;
	uint height = 480;

	gv = new GraphViewer(width, height, false);

	//Colocar a imagem “background.jpg” como fundo
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
			gv->setVertexSize((*it)->getInfo().getId(), 10);
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

RoadMap::~RoadMap(){}


