#include <iostream>
using namespace std;

//邻接表
class Graph {
private:
    // 边结点：用于链表中存储一条从某个顶点出发的边
    // vertex：这条边指向的顶点编号
    // weight：边的权重
    // next：指向同一出发顶点的下一条边
    struct EdgeNode {
        int vertex;
        int weight;
        EdgeNode *next;
    };
    // 顶点结点
    // vertex：顶点编号
    // firstEdge：指向从该顶点出发的第一条边（边链表的头指针）
    struct VertexNode {
        int vertex;
        EdgeNode *firstEdge;
    };
    // vertices：顶点个数
    // nodes：长度为 vertices 的顶点数组，nodes[i].firstEdge 指向从顶点 i 出发的边链表
    int vertices;
    VertexNode* nodes;

public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int u, int v, int w);
    void printGraph();
};

// 构造函数：创建一个有 vertices 个顶点的图
// 在堆上申请 vertices 个顶点结点，并将每个顶点的 firstEdge 置为 NULL
// 此时图中只有顶点，没有任何边
Graph::Graph(int vertices) {
    this->vertices = vertices;
    this->nodes = new VertexNode[vertices];
    for (int i = 0; i < vertices; ++i) {
        this->nodes[i].vertex = i;
        this->nodes[i].firstEdge = NULL;
    }
}

// 析构函数：
// 对每个顶点，沿着边链表依次 delete 掉所有 EdgeNode
// 最后 delete[] 顶点数组 nodes，防止内存泄漏
Graph::~Graph() {
    for (int i = 0; i < vertices; ++i) {
        EdgeNode* cur = nodes[i].firstEdge;
        while (cur) {
            EdgeNode* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
    delete[] nodes;
}

// 添加一条有向边 u -> v，权重为 w：
// 申请一个新的 EdgeNode，设置 vertex、weight
// 使用头插法，将其插入到顶点 u 的边链表头部
void Graph::addEdge(int u, int v, int w) {
    EdgeNode* newNode = new EdgeNode;
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = nodes[u].firstEdge;
    nodes[u].firstEdge = newNode;
}

// 打印图：对每个顶点 i，先打印 "Vertex i:"
// 然后沿着边链表依次打印从 i 出发的每条边的终点及其权重
void Graph::printGraph() {
    for (int i = 0; i < vertices; ++i) {
        EdgeNode* cur = nodes[i].firstEdge;
        cout << "Vertex " << i << ":" << endl;
        while (cur) {
            cout << cur->vertex << "(" << cur->weight << ") ";
            cur = cur->next;
        }
        cout << endl;
    }
}

int main() {
    Graph graph(5);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 4);
    graph.addEdge(3, 4, 2);

    graph.printGraph();
    return 0;
}