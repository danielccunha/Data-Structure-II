#include <string>
#include <list>

using std::string;
using std::list;

struct Edge;
struct Vertex
{
    int index;      // Índice do vértice na lista de vértices
    string label;   // Rótulo do vértice
    list<int> adj;  // Lista de adjacência
};

class Graph
{
    int V;              // Número de vértices
    list<Vertex> *adj;  // Lista de vértices

public:
    Graph(int V);    // Constructor
};

Graph::Graph(int V)
{
    this->V = V;
    this->adj = new list<Vertex>[V];
}