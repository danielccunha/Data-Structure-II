// Algoritmo feito com o intuito de validar as funções do grafo
#include "graph.cpp"
#include <cassert>
#include <cstdio>

int main()
{
    Graph g(4);
    g.addVertex(0, "aa");
    g.addVertex(1, "bb");
    g.addVertex(2, "cc");
    g.addVertex(3, "dd");
    
    assert(g.vertexUtil["aa"] == 0);
    assert(g.vertexUtil["bb"] == 1);
    assert(g.vertexUtil["cc"] == 2);
    assert(g.vertexUtil["dd"] == 3);

    g.addEdge(0, "V0", "aa", "bb", 5);
    g.addEdge(1, "V1", "aa", "cc", 12);
    g.addEdge(2, "V2", "aa", "dd", 9);
    g.addEdge(3, "V3", "bb", "cc", 2);
    g.addEdge(4, "V4", "bb", "dd", 3);
    g.addEdge(5, "V5", "cc", "dd", 11);

    assert(g.edgeUtil["V0"] == 0);
    assert(g.edgeList[0].label == "V0");
    assert(g.edgeList[0].w == 5);
    assert(g.edgeList[0].o == g.vertexUtil["aa"]);
    assert(g.edgeList[0].d == g.vertexUtil["bb"]);

    assert(g.edgeUtil["V1"] == 1);
    assert(g.edgeList[1].label == "V1");
    assert(g.edgeList[1].w == 12);
    assert(g.edgeList[1].o == g.vertexUtil["aa"]);
    assert(g.edgeList[1].d == g.vertexUtil["cc"]);

    assert(g.edgeUtil["V2"] == 2);
    assert(g.edgeList[2].label == "V2");
    assert(g.edgeList[2].w == 9);
    assert(g.edgeList[2].o == g.vertexUtil["aa"]);
    assert(g.edgeList[2].d == g.vertexUtil["dd"]);

    assert(g.edgeUtil["V3"] == 3);
    assert(g.edgeList[3].label == "V3");
    assert(g.edgeList[3].w == 2);
    assert(g.edgeList[3].o == g.vertexUtil["bb"]);
    assert(g.edgeList[3].d == g.vertexUtil["cc"]);

    assert(g.edgeUtil["V4"] == 4);
    assert(g.edgeList[4].label == "V4");
    assert(g.edgeList[4].w == 3);
    assert(g.edgeList[4].o == g.vertexUtil["bb"]);
    assert(g.edgeList[4].d == g.vertexUtil["dd"]);

    assert(g.edgeUtil["V5"] == 5);
    assert(g.edgeList[5].label == "V5");
    assert(g.edgeList[5].w == 11);
    assert(g.edgeList[5].o == g.vertexUtil["cc"]);
    assert(g.edgeList[5].d == g.vertexUtil["dd"]);

    printf("OK\n");

    return 0;
}