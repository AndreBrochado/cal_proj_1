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

		//TODO Falta conferir se os id estï¿½o em crossroads/roads.
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

	//Colocar a imagem ï¿½background.jpgï¿½ como fundo
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
			//gv->setVertexLabel((*it)->getInfo().getId(), ".");
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

void  RoadMap::bestPath(uint id_src, uint id_dest, list<uint>mustPass){
	double minDist = INT_MAX;
	vector<Crossroad> path;
	path.push_back(crossRoads.find(id_src)->second);

	gv->setVertexColor(id_src, "red");
	gv->setVertexSize(id_src, 20);

	gv->setVertexColor(id_dest, "orange");
	gv->setVertexSize(id_dest, 20);

	for(list<uint>::iterator it = mustPass.begin(); it != mustPass.end();it++){
		gv->setVertexColor(*it, "green");
		gv->setVertexSize(*it, 20);
	}

	getchar();
	if(bestPath(id_src, id_dest, mustPass, path, 0, minDist)){
		cout << minDist <<"m "<< endl;
		for (unsigned int i = 1; i < path.size(); ++i) {
			gv->setVertexColor(path[i].getId(),"yellow");
			gv->rearrange();
		}
	}
	else
		cout << "Caminho impossível\n";
}

bool RoadMap::bestPath(uint id_src, uint id_dest, list<uint>mustPass, vector<Crossroad> &path, double distSoFar, double &minDist){
	Crossroad src = crossRoads.find(id_src)->second;
	map<double,vector <Crossroad> > possiblePaths;
	vector <Crossroad> path_tmp = path;
	int count = 0;

	this->dijkstraShortestPath(src);

	if(mustPass.size() == 1){
		Crossroad dest = crossRoads.find(id_dest)->second;
		double distTotal = distSoFar + this->getVertex(dest)->getDist();

		path_tmp = getPath(src,dest);

		path.insert(path.end(),path_tmp.begin()+1,path_tmp.end());

		if(distTotal < minDist){
			count ++;
			minDist = distTotal;
			return true;
		}
		else
			return false;
	}
	else{
		for(list<uint>::iterator it = mustPass.begin(); it != mustPass.end();){
			Crossroad c = crossRoads.find(*it)->second;
			double dist = this->getVertex(c)->getDist();

			if(dist == INT_MAX){
				return false;
			}
			else if(dist == 0){
				it = mustPass.erase(it);
			}
			else{
				possiblePaths.insert(pair<double,vector <Crossroad> >(dist, getPath(src,c)));
				it++;
			}
		}

		for(map<double,vector <Crossroad> >::iterator it = possiblePaths.begin(); it != possiblePaths.end(); it++){
			if(distSoFar + it->first < minDist){
				vector <Crossroad> path_tmp2 = path_tmp;
				path_tmp2.insert(path_tmp2.end(),it->second.begin()+1,it->second.end());
				if(bestPath(path_tmp2.back().getId(), id_dest, mustPass, path_tmp2, distSoFar + it->first, minDist)){
					count ++;
					path = path_tmp2;
				}
			}
		}
	}

	if(count > 0)
		return true;
	else
		return false;
}

uint RoadMap::getNodeId(string roadName, double doorNumber){
	uint id = -1;

	for (map<uint, Road>::iterator it = roads.begin(); it != roads.end() && id == -1; it++) {
		id = it->second.getNodeId(roadName, doorNumber);
	}

	return id;
}

RoadMap::~RoadMap(){}


