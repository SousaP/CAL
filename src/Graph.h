#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
using namespace std;

template<class T> class Edge;
template<class T> class Graph;
const int INT_INFINITY = std::numeric_limits<int>::max();
/*
 * ================================================================================================
 * Vertice
 * ================================================================================================
 */
template<class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool visited;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T pess);
	friend class Graph<T> ;
	T getInfo();
	vector<Edge<T> > getEdges();
};

template <class T>
struct vertex_greater_than {
    bool operator()(Vertex<T> * a, Vertex<T> * b) const {
        return a->getDist() > b->getDist();
    }
};


template<class T>
vector<Edge<T> > Vertex<T>::getEdges() {
	return adj;
}

template<class T>
Vertex<T>::Vertex(T pess) :
		info(pess), visited(false) {
}

template<class T>
T Vertex<T>::getInfo() {
	return info;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest, w);
	adj.push_back(edgeD);
}

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		} else
			it++;
	}
	return false;
}

/*
 * ================================================================================================
 * Arestas
 * ================================================================================================
 */
template<class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T> ;
	friend class Vertex<T> ;
	T getDest();
	double getweight();
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

template<class T>
T Edge<T>::getDest() {
	return dest->getInfo();
}

template<class T>
double Edge<T>::getweight() {
	return weight;
}

/*
 * ================================================================================================
 * Grafo
 * ================================================================================================
 */
template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	void clone(Graph<T> &g);
	void dijkstraShortestPath(const T &s);
};

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vS->addEdge(vD, w);
	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	return vS->removeEdgeTo(vD);
}

template<class T>
void Graph<T>::clone(Graph<T> &gr) {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();

	// 1. clone vertices
	for (; it != ite; it++) {
		gr.addVertex((*it)->getInfo());
		gr.vertexSet[gr.getNumVertex() - 1]->visited = false;
	}

	// 2. clone edges
	for (it = vertexSet.begin(); it != ite; it++) {
		typename vector<Edge<T> >::iterator edgeIt = ((*it)->adj).begin();
		typename vector<Edge<T> >::iterator edgeIte = ((*it)->adj).end();
		for (; edgeIt != edgeIte; edgeIt++) {
			gr.addEdge((*it)->getInfo(), edgeIt->dest->getInfo(),
					edgeIt->weight);
		}
	}
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector<Vertex<T>*> pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());

	while (!pq.empty()) {

		/*
		 v = pq.front();
		 pop_heap(pq.begin(), pq.end());
		 pq.pop_back();
		 */

		pop_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
		v = pq.back();
		pq.pop_back();

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if (v->dist + v->adj[i].weight < w->dist) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se já estiver na lista, apenas a actualiza
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
			}
		}
	}
}

#endif /* GRAPH_H_ */
