/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <limits>
#include <vector>
#include <queue>

using namespace std;


const int infinity = std::numeric_limits<int>::max();

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	int indegree;
	int dist;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
	void decreaseIndegree();
	void increaseIndegree();
	void resetPathAndDist();
public:
	Vertex<T>* path;
	Vertex(T in);
	friend class Graph<T>;

	void deleteEdges();
	T getInfo() const;
	int getIndegree() const;
	void resetIndegree();
};

template <class T>
void Vertex<T>::resetPathAndDist(){
	dist = infinity;
	path = 0;
}

template <class T>
void Vertex<T>::decreaseIndegree(){
	indegree --;
}

template <class T>
void Vertex<T>::increaseIndegree(){
	indegree ++;
}

template <class T>
void Vertex<T>::deleteEdges(){
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		(it->dest)->decreaseIndegree();
		adj.erase(it);
		it++;
	}
}


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			(it->dest)->decreaseIndegree();
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), indegree(0), dist(infinity), path(0){}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
void Vertex<T>::resetIndegree(){
	indegree = 0;
}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
	dest->increaseIndegree();
}

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
	bool isDAG(Vertex<T> *v) const;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	bool isDAG();
	vector<T> topologicalOrder();
	void unweightedShortestPath(const T &v);
	vector<T> getPath(const T &origin, const T &dest);
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);

			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			v->deleteEdges();

			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,w);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	return vS->removeEdgeTo(vD);
}




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false )
			dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

//a)
template <class T>
void Graph<T>::resetIndegrees(){
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->resetIndegree();

	it= vertexSet.begin();
	for (; it !=ite; it++){
		Vertex<T>* v = *it;
		typename vector<Edge<T> >::iterator it2= (v->adj).begin();
		typename vector<Edge<T> >::iterator ite2= (v->adj).end();

		for (; it2 !=ite2; it2++)
			(it2->dest)->increaseIndegree();
	}
}

//b)
template <class T>
vector<Vertex<T>*> Graph<T>::getSources() const{
	vector<Vertex<T>*> res;

	for (int i = 0; i < vertexSet.size(); ++i) {
		if((vertexSet.at(i))->getIndegree() == 0)
			res.push_back(vertexSet.at(i));
	}

	return res;
}

//c)
template <class T>
bool Graph<T>::isDAG(Vertex<T> *v) const{
	vector<T> res;

	{
		typename vector<Edge<T> >::iterator it= (v->adj).begin();
		typename vector<Edge<T> >::iterator ite= (v->adj).end();

		for (; it !=ite; it++)
			if ( it->dest->visited == false )
				dfs(it->dest, res);
	}

	typename vector<T>::iterator it= res.begin();
	typename vector<T>::iterator ite = res.end();
	for (; it !=ite; it++)
		if (*it == v->info)
			return false;

	return true;

}

template <class T>
bool Graph<T>::isDAG(){
	typename vector<Vertex<T>*>::const_iterator it1= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator it2= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();

	for (; it2 !=ite; it2++){
		for (it1= vertexSet.begin(); it1 !=ite; it1++)
			(*it1)->visited=false;
		if(!isDAG(*it2))
			return false;
	}
	return true;
}

//d)
template <class T>
vector<T> Graph<T>::topologicalOrder(){
	queue<Vertex<T>* > C;

	{
		typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
		typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
		for (; it !=ite; it++)
			if((*it)->getIndegree() == 0)
				C.push(*it);
	}

	vector<T> res;

	while (!C.empty()) {
		Vertex<T>* v = C.front();
		C.pop();

		res.push_back(v->info);

		typename vector<Edge<T> >::iterator it= (v->adj).begin();
		typename vector<Edge<T> >::iterator ite= (v->adj).end();

		for (; it !=ite; it++){
			Vertex<T>* w = it->dest;
			w->decreaseIndegree();
			if(w->getIndegree() == 0)
				C.push(w);
		}
	}

	resetIndegrees();

	// Terminação
	if (res.size() != vertexSet.size())
		res.clear();

	return res;
}

//e)
template <class T>
void Graph<T>::unweightedShortestPath(const T &v){
	Vertex<T>* s;

	{
		typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
		typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
		for (; it !=ite; it++){
			(*it)->resetPathAndDist();
			if((*it)->getInfo() == v)
				s = *it;
		}
	}

	s->dist = 0;
	queue<Vertex<T>*> q;

	q.push(s); // na cauda

	while( ! q.empty() ) {
		Vertex<T>* tmp = q.front();
		q.pop();

		typename vector<Edge<T> >::iterator it= (tmp->adj).begin();
		typename vector<Edge<T> >::iterator ite= (tmp->adj).end();

		for (; it !=ite; it++){
			Vertex<T>* w = it->dest;
			if(w->dist == infinity){
				w->dist = tmp->dist + 1;
				w->path = tmp;
				q.push(w);
			}
		}
	}
}

template <class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){
	unweightedShortestPath(origin);
	Vertex<T>* v;
	vector<T> res;

	{
		typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
		typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
		for (; it !=ite; it++)
			if((*it)->getInfo() == dest)
				v = *it;
	}

	res.push_back(v->info);

	while(v->path != 0){
		v = v->path;
		res.push_back(v->info);
	}

	reverse(res.begin(),res.end());

	return res;
}


#endif /* GRAPH_H_ */
