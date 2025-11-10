#include <iostream>
using namespace std;

//二叉树结点定义
template<typename T>
struct TreeNode {
    T val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(NULL), right(NULL) {}
    TreeNode(T x) : val(x), left(NULL), right(NULL) {}
};

//二叉树类定义
template<typename T>
class Tree {
private:
    TreeNode<T> *nodes;//二叉树结点池
    TreeNode<T> *root;//根节点
    size_t nodeSize;//结点池大小

    TreeNode<T>* Create(T a[], int size, int nodeId, T nullnode);
    void visit(TreeNode<T> *node);
    void preOrder(TreeNode<T> *node);
    void inOrder(TreeNode<T> *node);
    void postOrder(TreeNode<T> *node);
    void levelOrder(TreeNode<T> *node);
public:
    Tree();
    Tree(int maxNodes);
    ~Tree();
    TreeNode<T> *getTreeNode(int id);
    void CreateTree(T a[], int size, T nullnode);
    void preOrderTraversal();
    void inOrderTraversal();
    void postOrderTraversal();

};

template<typename T>
Tree<T>::Tree() {
    nodeSize = 100001;
    nodes = new TreeNode<T>[nodeSize];
}

template<typename T>
Tree<T>::Tree(int maxNodes) {
    nodeSize = maxNodes;
    nodes = new TreeNode<T>[nodeSize];
}

template<typename T>
Tree<T>::~Tree() {
    delete[] nodes;
}

template<typename T>
TreeNode<T> *Tree<T>::getTreeNode(int id) {
    return &nodes[id];
}

template<typename T>
void Tree<T>::visit(TreeNode<T> *node) {
    cout << node->val;
}

template<typename T>
void Tree<T>::preOrder(TreeNode<T> *node) {
    if (node) {
        visit(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

template<typename T>
void Tree<T>::inOrder(TreeNode<T> *node) {
    if (node) {
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}

template<typename T>
void Tree<T>::postOrder(TreeNode<T> *node) {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}

template<typename T>
void Tree<T>::CreateTree(T a[], int size, T nullnode) {
    root = Create(a, size, 1, nullnode);
}

template<typename T>
TreeNode<T> *Tree<T>::Create(T a[], int size, int nodeId, T nullnode) {
    if (nodeId >= size || a[nodeId] == nullnode) {
        return NULL;
    }
    TreeNode<T>* nowNode = getTreeNode(nodeId);
    nowNode->val = a[nodeId];
    nowNode->left = Create(a, size, nodeId * 2, nullnode);
    nowNode->right = Create(a, size, nodeId * 2 + 1, nullnode);
    return nowNode;
}

template<typename T>
void Tree<T>::preOrderTraversal() {
    preOrder(root);
}

template<typename T>
void Tree<T>::inOrderTraversal() {
    inOrder(root);
}

template<typename T>
void Tree<T>::postOrderTraversal() {
    postOrder(root);
}

int main() {
    const char nullnode = '-';
    char a[15] = {
        nullnode, 'a', 'b', 'c', 'd',
        nullnode, 'e', 'f', 'g', 'h',
        nullnode, nullnode, nullnode, nullnode, 'i'
    };

    Tree<char> T(15);
    T.CreateTree(a, 15, nullnode);
    T.preOrderTraversal(); cout << endl;
    T.inOrderTraversal(); cout << endl;
    T.postOrderTraversal(); cout << endl;
    return 0;
}