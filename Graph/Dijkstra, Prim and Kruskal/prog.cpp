#include "graph.cpp"
#include <iostream>

using namespace std;

int main()
{
    int V, E;
    string label;

    cout << "Number of vertex: ";
    cin  >> V;
    Graph g(V);

    for(int i = 0; i < V; ++i)
    {
        cin >> label;
        g.addVertex(i, label);
    }

    for(int i = 0; i < V; ++i)
        cout << "List[" << g.list[i].index << "] = " << g.list[i].label << endl;
    
    cout << "Number of edges: ";
    cin  >> E;

    string orig, dest;
    int weight;

    while(E--)
    {
        cin >> label >> orig >> dest >> weight;
        g.addEdge(label, orig, dest, weight);
    }

    return 0;
}