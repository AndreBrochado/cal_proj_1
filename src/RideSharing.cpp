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


	User u1 = User("Bruno","Regua");
	//Hora teste = Hora(20,30);

	//u1.setArrivalTime(teste);
	//cout << u1.returnArrivalTime() << endl;

	getchar();

	return 0;
}





