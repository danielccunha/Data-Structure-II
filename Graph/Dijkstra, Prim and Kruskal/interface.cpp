#include "graph.cpp"
#include <iostream>
#include <functional>

using std::cin;
using std::cout;

// Imprime o menu de opções
void menu()
{
    cout << "\tMENU\n";
    cout << "L - Leitura\tD - Dijkstra\n";
    cout << "P - Prim\tK - Kruskal\n";
    cout << "M - Menu\tF - Fim\n";
}