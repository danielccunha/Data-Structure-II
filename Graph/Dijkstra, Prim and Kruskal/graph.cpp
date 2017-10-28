#include <string>
#include <list>
#include <vector>
#include <map>

using std::string;
using std::list;
using std::vector;
using std::map;

struct Edge;
struct Vertex
{
    int index;      // Índice do vértice na lista de vértices
    string label;   // Rótulo do vértice
    list<Edge> adj;  // Lista de adjacência

    Vertex(int index, string label) // Constructor
    {
        this->index = index;
        this->label = label;
    }    
};

struct Edge
{
    string label;   // Rótulo
    int w;          // Weight/Peso
    int d;          // Destiny/Destino -> índice do vértice destino na lista de vértices

    Edge(string label, int index, int weight)
    {
        this->label = label;
        this->d     = index;
        this->w     = weight;
    }
};

class Graph
{
    int V;  // Número de vértices

protected:
    Edge getNewEdge(string label, int destiny, int weight);

public:
    vector<Vertex> list;        // Lista de vértices
    map<string, int> indexUtil; // Map auxiliar para armazenar o índice do vértice na lista de vértices

    Graph(int V);    // Constructor
    void addVertex(int index, string label);    // Adiciona um vértice ao grafo
    void addEdge(string label, string orig, string dest, int weight); // Adiciona uma aresta ao grafo
};

Graph::Graph(int V)
{
    this->V = V;
}

void Graph::addVertex(int index, string label)
{
    Vertex tmp(index, label);
    list.push_back(tmp);
    indexUtil[label] = index;
}

Edge Graph::getNewEdge(string label, int destiny, int weight)
{
    Edge tmp(label, destiny, weight);
    return tmp;
}

void Graph::addEdge(string label, string orig, string dest, int weight)
{
    // Índices dos vértices
    int i = indexUtil[orig], j = indexUtil[dest];

    list[i].adj.push_back(getNewEdge(label, j, weight));
    list[j].adj.push_back(getNewEdge(label, i, weight));
}