#include <map>
#include <list>

using std::map;
using std::list;

class Graph
{
	map<int, list<int> > adj;	// Lista de adjacência

public:
	void addEdge(int v, int w);	// Adiciona uma aresta ao grafo
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}