#include <iostream>
using namespace std;

#define inf -1

class Graph {
private:
    int vertices;
    int** edges;
public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int u, int v, int w);
    void printGraph();
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    edges = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        edges[i] = new int[vertices];
        for (int j = 0; j < vertices; ++j) {
            edges[i][j] = inf;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < vertices; ++i) {
        delete[] edges[i];
    }
    delete[] edges;
}

void Graph::addEdge(int u, int v, int w) {
    edges[u][v] = w;
}

void Graph::printGraph() {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 0, 6);
    g.printGraph();
    return 0;
}