#include "Ridesharing.h"



using namespace std;

int main(){

	//Teste GraphViewer
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->createWindow(600, 600);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);

	gv->addEdge(0,0,1,EdgeType::UNDIRECTED);

	gv->rearrange();

	App application;

	application.AddUser("Bruno", "porto");
	User* u = new User("Bruno" , "porto");
	application.AddCar(*u, 5, "adsk", "coisa");



	getchar();

	return 0;
}





