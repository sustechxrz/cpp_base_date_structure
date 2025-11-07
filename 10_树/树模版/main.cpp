#include <iostream>
using namespace std;

// 模板链表节点，用于存储任意类型 T 的数据。每个节点包含一个 data 成员和一个指向下一个节点的 next 指针。
template<typename T>
struct ListNode {
    T data;
    ListNode *next;
    ListNode(T d) : data(d), next(NULL) {}
};

// 模板树节点，节点含有模板成员变量 data 存储数据，
// childrenHead 指向一个链表，该链表中每个节点的 data 都是指向一个子节点（TreeNode<T>*）的指针。
template<typename T>
struct TreeNode {
    T data;
    ListNode< TreeNode<T>* >* childrenHead;

    //树结点构造函数，初始时当前节点无孩子结点
    TreeNode() {
        childrenHead = NULL;
    }

    //添加孩子节点函数
    void AddChild(TreeNode<T>* node) {
        // 在堆上动态创建一个新的 ListNode 对象，用于存储子节点指针。
        // 若当前节点没有子节点，则 childrenHead 指向新创建的节点；
        // 否则使用头插法将该节点插入孩子链表前端，并更新 childrenHead。
        ListNode< TreeNode<T>* >* childNode = new ListNode<TreeNode<T> *>(node);
        if (childrenHead == NULL) {
            childrenHead = childNode;
        }
        else {
            childNode->next = childrenHead;
            childrenHead = childNode;
        }
    }
};

// 模板树类。包含：
// 1) root：指向根节点的指针；
// 2) nodes：指向动态分配的 TreeNode 数组（节点池），用于集中存储所有节点。
template<typename T>
class Tree {
private:
    TreeNode<T>* nodes;
    TreeNode<T>* root;

public:
    //树构造函数
    Tree();
    Tree(int maxNodes);
    //树析构函数
    ~Tree();
    //根据节点 id 返回对应的 TreeNode 指针。
    TreeNode<T>* GetTreeNode(int id);
    //设置根节点函数，将输入的结点id对应的树结点设置为根结点
    void SetRoot(int id);
    // 将 sonId 对应的节点设为 parentId 对应节点的子节点，
    // 内部通过调用父节点的 AddChild() 实现。
    void AddChild(int parentId, int sonId);
    //给输入的id对应的树结点的分配数据data
    void AssignData(int id, T data);
    // 递归打印整棵树（先序遍历）。
    // 若 node 为 NULL，从根节点开始。
    // 对于每个节点：先输出当前节点 data，再递归打印所有子节点。
    void Print(TreeNode<T>* node = NULL);
};

template<typename T>
Tree<T>::Tree() {
    nodes = new TreeNode<T>[100001];
}

template<typename T>
Tree<T>::Tree(int maxNodes) {
    nodes = new TreeNode<T>[maxNodes];
}

template<typename T>
Tree<T>::~Tree() {
    delete[] nodes;
}

template<typename T>
TreeNode<T>* Tree<T>::GetTreeNode(int id) {
    return &nodes[id];
}

template<typename T>
void Tree<T>::SetRoot(int id) {
    root = GetTreeNode(id);
}

template<typename T>
void Tree<T>::AddChild(int parentId, int sonId) {
    TreeNode<T>* parentNode = GetTreeNode(parentId);
    TreeNode<T>* sonNode = GetTreeNode(sonId);
    parentNode->AddChild(sonNode);
}

template<typename T>
void Tree<T>::AssignData(int id, T data) {
    GetTreeNode(id)->data = data;
}

template<typename T>
void Tree<T>::Print(TreeNode<T>* node) {
    if (node == NULL) {
        node = root;
    }
    cout << node->data;
    ListNode<TreeNode<T>* >* tmp = node->childrenHead;
    while (tmp) {
        Print(tmp->data);
        tmp = tmp->next;
    }
}

int main() {
    Tree<char> T(9);
    T.SetRoot(0);
    T.AssignData(0,'a');
    T.AssignData(1,'b');
    T.AssignData(2,'c');
    T.AssignData(3,'d');
    T.AssignData(4,'e');
    T.AssignData(5,'f');
    T.AssignData(6,'g');
    T.AssignData(7,'h');
    T.AssignData(8,'i');

    T.AddChild(0,1);
    T.AddChild(0,2);
    T.AddChild(1,3);
    T.AddChild(2,4);
    T.AddChild(2,5);
    T.AddChild(3,6);
    T.AddChild(3,7);
    T.AddChild(3,8);

    T.Print();

    return 0;
}