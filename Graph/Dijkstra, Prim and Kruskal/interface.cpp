#include "graph.cpp"
#include <iostream>
#include <fstream>
#include <functional>

using std::cin;
using std::cout;
using std::ifstream;

// Arquivo de entrada do grafo
#define FILE "ENTRADA_GRAFO.txt"

// Grafo para ser inicializado
Graph *g;

// Imprime o menu de opções
void menu()
{
    cout << "\tMENU\n";
    cout << "L - Leitura\tD - Dijkstra\n";
    cout << "P - Prim\tK - Kruskal\n";
    cout << "M - Menu\tF - Fim\n";
}
std::function<void()> M = menu;

// Lê o arquivo de entrada
void leitura()
{
    ifstream input(FILE);
    int V, E;     // Vértices, Arestas
    string label; // Rótulo

    input >> V; // Número de vértices
    g = new Graph(V); // Cria o grafo

    for(int i = 0; i < V; ++i) // Lê os rótulos dos vértices
    {
        input >> label;
        g->addVertex(i, label);
    }

    input >> E; // Número de arestas
    string orig, dest;
    int weight;

    while(E--)  // Lê as arestas
    {
        input >> label >> orig >> dest >> weight;
        g->addEdge(label, orig, dest, weight);
    }
}
std::function<void()> L = leitura;

// Chama o método Dijkstra
// void dijkstra();
// std::function<void()> D = dijkstra;

// Chama o método Prim
// void prim();
// std::function<void()> P = prim;

// Chama o método Kruskal
// void kruskal();
// std::function<void()> K = kruskal;

map<char, std::function<void()> > function{ {'M', M}, {'L', L} };