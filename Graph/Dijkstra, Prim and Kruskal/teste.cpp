// Algoritmo de teste para priority queue
#include <iostream>
#include <queue>

using namespace std;

struct Edge
{
    string label;   // Rótulo
    int w;          // Weight

    Edge(string label, int weight)
    {
        this->label = label;
        this->w     = weight;
    }

    bool operator<(const Edge& tmp) const
    {
        return w > tmp.w;
    }
};

int main()
{
    priority_queue<Edge> pq;

    Edge e1("aa", 50), e2("bb", 70), e3("cc", 30), e4("dd", 30);
    Edge aux("AA", 10);

    pq.push(e1);
    pq.push(e2);
    pq.push(e3);
    pq.push(e4);

    while(!pq.empty())
    {
        aux = pq.top();
        pq.pop();

        cout << aux.w << "\t" << aux.label << endl;
    }

    return 0;
}