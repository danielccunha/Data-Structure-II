#include "graph.cpp"

int main()
{
	Graph g;

	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	g.addEdge(3, 5);
	g.addEdge(4, 6);
	g.addEdge(4, 5);
	g.addEdge(5, 6);

	g.DFS(1);	// 1 2 4 6 5 3
	g.BFS(1);	// 1 2 3 4 5 6

	return 0;
}