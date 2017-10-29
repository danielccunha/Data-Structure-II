// Algoritmo feito com o intuito de validar as funções do grafo
#include "graph.cpp"
#include <cassert>

int main()
{
    Graph g(4);
    g.addVertex(0, "aa");
    g.addVertex(1, "bb");
    g.addVertex(2, "cc");
    g.addVertex(3, "dd");
    g.addEdge("V0", "aa", "bb", 10);
    g.addEdge("V1", "aa", "dd", 15);
    g.addEdge("V2", "aa", "cc", 20);
    g.addEdge("V3", "bb", "cc", 25);
    g.addEdge("V4", "cc", "dd", 30);

    // Valida os índices
    assert(g.indexUtil["aa"] == 0);
    assert(g.indexUtil["bb"] == 1);
    assert(g.indexUtil["cc"] == 2);
    assert(g.indexUtil["dd"] == 3);
    assert(g.list[0].index == 0);
    assert(g.list[1].index == 1);
    assert(g.list[2].index == 2);
    assert(g.list[3].index == 3);

    // Valida os rótulos
    assert(g.list[0].label == "aa");
    assert(g.list[1].label == "bb");
    assert(g.list[2].label == "cc");
    assert(g.list[3].label == "dd");

    // Valida o tamanho das listas de adjacência
    assert(g.list[0].adj.size() == 3);
    assert(g.list[1].adj.size() == 2);
    assert(g.list[2].adj.size() == 3);
    assert(g.list[3].adj.size() == 2);

    // Valida as arestas
    assert(g.list[0].adj.front().label == "V0");
    assert(g.list[0].adj.front().d == g.indexUtil["bb"]);
    assert(g.list[0].adj.front().w == 10);
    assert(g.list[1].adj.front().label == "V0");
    assert(g.list[1].adj.front().d == g.indexUtil["aa"]);
    assert(g.list[1].adj.front().w == 10);
    
    auto it = g.list[0].adj.begin(); it++;
    assert(it->label == "V1");
    assert(it->d == g.indexUtil["dd"]);
    assert(it->w == 15);
    assert(g.list[3].adj.front().label == "V1");
    assert(g.list[3].adj.front().d == g.indexUtil["aa"]);
    assert(g.list[3].adj.front().w == 15);
    
    assert(g.list[0].adj.back().label == "V2");
    assert(g.list[0].adj.back().d == g.indexUtil["cc"]);
    assert(g.list[0].adj.back().w == 20);
    assert(g.list[2].adj.front().label == "V2");
    assert(g.list[2].adj.front().d == g.indexUtil["aa"]);
    assert(g.list[2].adj.front().w == 20);

    assert(g.list[1].adj.back().label == "V3");
    assert(g.list[1].adj.back().d == g.indexUtil["cc"]);
    assert(g.list[1].adj.back().w == 25);
    it = g.list[2].adj.begin(); it++;
    assert(it->label == "V3");
    assert(it->d == g.indexUtil["bb"]);
    assert(it->w == 25);
    
    // g.addEdge("V4", "cc", "dd", 30);
    assert(g.list[2].adj.back().label == "V4");
    assert(g.list[2].adj.back().d == g.indexUtil["dd"]);
    assert(g.list[2].adj.back().w == 30);
    assert(g.list[3].adj.back().label == "V4");
    assert(g.list[3].adj.back().d == g.indexUtil["cc"]);
    assert(g.list[3].adj.back().w == 30);    

    return 0;
}