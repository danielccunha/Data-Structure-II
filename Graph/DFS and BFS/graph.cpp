// Grafo direcionado implementado para a matéria de Estrutura de Dados II
#include <map>
#include <list>
#include <queue>
#include <cstdio>

using std::map;
using std::list;
using std::queue;

class Graph
{
	map<int, list<int> > adj;	// Lista de adjacência
	void DFSUtil(int s, map<int, bool> &visited);

public:
	void addEdge(int v, int w);	// Adiciona uma aresta ao grafo
	void DFS(int s);	// Imprime o grafo realizando uma DFS (Caso não exista caminho entre o vértice s e algum outro nodo, este nodo não será impresso)
	void BFS(int s);	// Imprime o grafo realizando uma BFS (Caso não exista caminho entre o vértice s e algum outro nodo, este nodo não será impresso)
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

void Graph::DFS(int s)
{
	// Cria um map para os vértices, todos iniciados como false
	map<int, bool> visited;

	// Chama a função auxiliar da DFS
	DFSUtil(s, visited);
	printf("\n");
}

void Graph::DFSUtil(int s, map<int, bool> &visited)
{
	// Marca o vértice como visitado e imprime seu valor
	visited[s] = true;
	printf("%d ", s);

	// Chama a função recursivamente para cada vértice ainda não visitado
	for(auto it = adj[s].begin(); it != adj[s].end(); ++it)
		if(!visited[*it])
			DFSUtil(*it, visited);
}

void Graph::BFS(int s)
{
	// Cria um map para os vértices, todos iniciados como false
	map<int, bool> visited;

	// Cria uma fila para a BFS
	queue<int> q;

	// Empilha o vértice s
	q.push(s);

	// Realiza a BFS enquanto houver vértices na fila
	while(!q.empty())
	{
		// Retira um vértice do ínicio da fila
		// O marca como visitado e o imprime
		s = q.front();
		q.pop();
		printf("%d ", s);

		// Adiciona ao fim da vila todos os vértices adjacentes de s
		for(auto it = adj[s].begin(); it != adj[s].end(); ++it)
			if(!visited[*it])
			{
				q.push(*it);
				visited[*it] = true;
			}
	}
	printf("\n");
}