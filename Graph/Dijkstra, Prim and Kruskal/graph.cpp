#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <climits>      // INT_MAX

#define INF INT_MAX // Constante infita para o método Dijkstra

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::map;
using std::priority_queue;

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
    int w;          // Peso
    int o;          // Origem  -> índice do vértice origem
    int d;          // Destino -> índice do vértice destino na lista de vértices

    Edge(string label, int origin, int dest, int weight)
    {
        this->label = label;
        this->o     = origin;
        this->d     = dest;
        this->w     = weight;
    }

    bool operator<(const Edge& tmp) const
    {
        return w > tmp.w;
    }
};

class Graph
{
    int V;  // Número de vértices

protected:
    struct dijkstraUtil;
    struct primUtil;
    Edge getNewEdge(string label, int origin, int destiny, int weight); // Função auxiliar para adicionar uma aresta ao grafo
    int  shorterDist(dijkstraUtil table[]); // Função auxiliar para encontrar o índice não finalizado com menor custo da tabela no algoritmo de dijkstra

public:
    vector<Vertex> vertexList;         // Lista de vértices
    vector<Edge>   edgeList;
    map<string, int> vertexUtil; // Map auxiliar para armazenar o índice do vértice na lista de vértices
    map<string, int> edgeUtil;   // Map auxiliar para armazenar o índice da aresta na lista de arestas

    Graph(int V);    // Constructor
    void addVertex(int index, string label);    // Adiciona um vértice ao grafo
    void addEdge(int index, string label, string orig, string dest, int weight); // Adiciona uma aresta ao grafo
    void dijkstra(string source, string dest);  // Executa o algoritmo de 
    void prim(string source);
};

Graph::Graph(int V)
{
    this->V = V;
}

void Graph::addVertex(int index, string label)
{
    Vertex tmp(index, label);
    vertexList.push_back(tmp);
    vertexUtil[label] = index;
}

Edge Graph::getNewEdge(string label, int origin, int destiny, int weight)
{
    Edge tmp(label, origin, destiny, weight);
    return tmp;
}

void Graph::addEdge(int index, string label, string orig, string dest, int weight)
{
    // Índices dos vértices
    int i = vertexUtil[orig], j = vertexUtil[dest];

    vertexList[i].adj.push_back(getNewEdge(label, i, j, weight));
    vertexList[j].adj.push_back(getNewEdge(label, j ,i, weight));

    edgeList.push_back(getNewEdge(label, i, j, weight));
    edgeUtil[label] = index;
}

// Estrutura auxiliar para a execução do algoritmo de Dijkstra
struct Graph::dijkstraUtil
{
    int dist, previous;
    bool visited;

    dijkstraUtil()       // Para cada nodo do grafo
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

    int v = vertexUtil[source];  // Acha o índice da origem
    table[v].dist = 0; // Zera o custo da origem

    int rest = V; // Variável de controle para executar o método enquanto houve nodo a ser visitado
    int aux, n;   // Variável auxiliar, neighbor

    while(rest--)
    {
        v = shorterDist(table); // Pega o índice do vértice com menor custo
        table[v].visited = true;

        // Caso índice com o menor custo seja o destino, ele sai do laço
        if(vertexList[v].label == dest) break;

        for(auto it = vertexList[v].adj.begin(); it != vertexList[v].adj.end(); ++it)
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
    cout << "Rótulo\tVisitado\tCusto\tCaminho\n";
    for(int i = 0; i < V; ++i)
    {
        cout << vertexList[i].label << "\t";
        (table[i].visited) ? cout << "TRUE\t\t" : cout << "FALSE\t\t";
        (table[i].dist != INF) ? cout << table[i].dist << "\t" : cout << "INF\t";
        
        if(table[i].previous == -1) // Caso seja a origem ou não foi visitado
            (vertexList[i].label == source) ? cout << "ORIGEM\n" : cout << "NULL\n";
        else
        {
            aux = table[i].previous;

            while(aux != -1)
            {
                cout << vertexList[aux].label;
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

// Estrutura auxiliar para a execução do algoritmo de Prim
struct Graph::primUtil
{
    bool visited;

    primUtil()
    {
        visited = false;
    }
};

void Graph::prim(string source)
{
    int i = vertexUtil[source]; // Índice do vértice de origem
    int E = edgeList.size();    // Número de arestas
    int T = V - 1;              // Número de vértices menos o fonte

    priority_queue<Edge> edgeQueue; // Fila de prioridade para as arestas
    primUtil table[E];              // Tabela de controle
    list<int> notInTree;            // Lista contendo os vértices que ainda não foram inseridos

    for(int j=0; j<V; ++j)
        if(j != i)
            notInTree.push_back(j);

    int aux;
    for(auto it = vertexList[i].adj.begin(); it != vertexList[i].adj.end(); ++it)
    {
        aux = edgeUtil[it->label]; // Índice da aresta    
        table[aux].visited = true;
        edgeQueue.push(*it);
    }
}