#include "graph.cpp"
#include <fstream>
#include <functional>
#include <cctype>

using std::ifstream;

// Arquivo de entrada do grafo
#define FILE "ENTRADA_GRAFO.txt"

// Grafo para ser inicializado
Graph *g;

// Ponteiros para as funções
void menu();        std::function<void()> M = menu;
void leitura();     std::function<void()> L = leitura;
void dijkstra();    std::function<void()> D = dijkstra;
void prim();        std::function<void()> P = prim;
void kruskal();     std::function<void()> K = kruskal;

// Mapa de ponteiros
map<char, std::function<void()> > function{{'M', M}, {'L', L}, {'D', D}, {'P', P}, {'K', K}};

int main()
{
    cout << "Desenvolvido por: Daniel de Almeida Cruz da Cunha - 158943@upf.br\n";
    char option;
    set<char> validOptions{'L', 'D', 'P', 'K', 'M'};

    menu();
    while(cout << "\nOpção: " && cin >> option && option != 'F' && option != 'f')
    {
        if(islower(option)) option = toupper(option);
        
        if(!validOptions.count(option)) // Caso o caracter lido não for encontrado no Set
            cout << "Opção inválida.\n";
        else
            function[option]();
    }

    return 0;
}

// Imprime o menu de opções
void menu()
{
    cout << "\n\tMENU\n";
    cout << "L - Leitura\tD - Dijkstra\n";
    cout << "P - Prim\tK - Kruskal\n";
    cout << "M - Menu\tF - Fim\n";
}

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

    for(int i = 0; i < E; ++i)  // Lê as arestas
    {
        input >> label >> orig >> dest >> weight;
        g->addEdge(i, label, orig, dest, weight);
    }
}

// Chama o método Dijkstra
void dijkstra()
{
    string source, dest;
    cout << "Origem:  ";
    cin  >> source;
    cout << "Destino: ";
    cin  >> dest;
    
    g->dijkstra(source, dest);
}

// Chama o método Prim
void prim()
{
    string source;
    cout << "Origem: ";
    cin  >> source;

    g->prim(source);
}

// Chama o método Kruskal
void kruskal()
{
    g->kruskal();
}