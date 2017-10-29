#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <climits>      // INT_MAX

#define INF INT_MAX // Constante infita para o método Dijkstra

using std::cin;
using std::cout;
using std::endl;
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
    struct dijkstraUtil;
    Edge getNewEdge(string label, int destiny, int weight); // Função auxiliar para adicionar uma aresta ao grafo
    int shorterDist(dijkstraUtil table[]); // Função auxiliar para encontrar o índice não finalizado com menor custo da tabela no algoritmo de dijkstra

public:
    vector<Vertex> list;        // Lista de vértices
    map<string, int> indexUtil; // Map auxiliar para armazenar o índice do vértice na lista de vértices

    Graph(int V);    // Constructor
    void addVertex(int index, string label);    // Adiciona um vértice ao grafo
    void addEdge(string label, string orig, string dest, int weight); // Adiciona uma aresta ao grafo
    void dijkstra(string source, string dest);  // Executa o algoritmo de 
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

/*
   	function Dijkstra(Graph, source):
     	for each vertex v in Graph: 	// Initialization
 	        dist[v] := infinity 	// initial distance from source to vertex v is set to infinite
	        previous[v] := undefined 	// Previous node in optimal path from source
         
        dist[source] := 0 	// Distance from source to source
 	    Q := the set of all nodes in Graph 	// all nodes in the graph are unoptimized - thus are in Q
 	    while Q is not empty: 	// main loop
 	        u := node in Q with smallest dist[ ]
 	        remove u from Q
 	        for each neighbor v of u: 	// where v has not yet been removed from Q.
 	        alt := dist[u] + dist_between(u, v)
 	        if alt < dist[v] 	// Relax (u,v)
 	            dist[v] := alt
 	            previous[v] := u
 	    return previous[ ] 
*/

// Estrutura auxiliar para a execução do algoritmo de Dijkstra
struct Graph::dijkstraUtil
{
    int dist, previous;
    bool visited;

    dijkstraUtil() // Para cada nodo do grafo
    {
        dist = INF;      // Declara o custo dele como infinito
        previous = -1;   // O índice do seu anterior como inválido
        visited = false; // E como não visitado
    }
};

void Graph::dijkstra(string source, string dest)
{
    // Distância (custo) da origem, índice do vértice que o antecede no caminho e uma flag para caso tenho sido finalizado
    dijkstraUtil table[V];

    int v = indexUtil[source];  // Acha o índice da origem
    table[v].dist = 0; // Zera o custo da origem

    int rest = V; // Variável de controle para executar o método enquanto houve nodo a ser visitado
    int aux, n;   // Variável auxiliar, neighbor

    while(rest--)
    {
        v = shorterDist(table); // Pega o índice do vértice com menor custo
        table[v].visited = true;

        for(auto it = list[v].adj.begin(); it != list[v].adj.end(); ++it)
        {
            n = it->d; // Índice do vértice destino
            if(!table[n].visited)
            {
                aux = table[v].dist + it->w; // Custo de v + peso da aresta

                if(aux < table[n].dist)
                {
                    table[n].dist = aux;
                    table[n].previous = v;
                }
            }
        }
    }

    // Imprimir a tabela com os dados
    cout << "\nDijkstra: " << source << " to " << dest << endl;
    cout << "Rótulo\tCusto\tCaminho\n";
    for(int i = 0; i < V; ++i)
    {
        cout << list[i].label << "\t" << table[i].dist << "\t";
        if(list[i].label == source) // Caso seja a origem
            cout << "ORIGEM\n";
        else
        {
            aux = table[i].previous;

            while(aux != -1)
            {
                cout << list[aux].label;
                aux = table[aux].previous;
                (aux == -1) ? cout << "\n" : cout << " ";
            }
        }
    }
}

int Graph::shorterDist(dijkstraUtil table[])
{
    int min = INF, i; // Menor custo encontrado, índice do menor custo
    for(int j = 0; j < V; ++j)
        if(!table[j].visited && table[j].dist < min)
        {
            min = table[j].dist;
            i = j;
        }

    return i;
}