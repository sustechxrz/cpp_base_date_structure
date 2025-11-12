#include <iostream>
using namespace std;

//模版树节点
template<typename T>
struct TreeNode {
    T val; //树节点的数据域
    TreeNode *left; //左孩子指针
    TreeNode *right; //右孩子指针
    TreeNode() : val(0), left(NULL), right(NULL) {} //空构造函数，val为0，左、右孩子指针为空
    TreeNode(T value) : val(value), left(NULL), right(NULL) {} //带数据域参数的构造函数，将val赋值为传进来的value
};

//二叉搜索树模版
/*
二叉搜索树（二叉排序树、二叉查找树）的性质：
1.空树是二叉搜索树
2.若左子树不为空，则左子树上所有节点的值均小于它根节点的值
3.若右子树不为空，则右子树上所有节点的值均大于它根节点的值
4.它的左右子树均为二叉搜索树
*/
template<typename T>
class BinarySearchTree {
private://私有成员
    TreeNode<T> *root; //指向根节点的指针
    TreeNode<T>* insertNode(TreeNode<T>* node, T value); //插入树节点，传入指向要插入的节点的指针和它的值的大小
    TreeNode<T>* deleteNode(TreeNode<T>* node, T value); //删除树节点，传入指向要删除的节点的指针和它的值的大小
    bool searchNode(TreeNode<T>* node, T value); //搜索传入的树节点
    void inOrder(TreeNode<T>* node);    //中序遍历，左根右，根据二叉搜索树的定义，中序遍历应该是一个递增的序列

public://公有成员
    BinarySearchTree() : root(NULL) {} //BST的空构造函数
    ~BinarySearchTree();    //析构函数

    //外部调用的插入接口
    void insert(T value) {
        root = insertNode(root, value);
    }
    //外部调用的删除接口
    void remove(T value) {
        root = deleteNode(root, value);
    }
    //外部调用的搜索接口
    bool search(T value) {
        return searchNode(root, value);
    }
    //外部调用的中序遍历接口
    void inOrderTraversal() {
        inOrder(root);
        cout << endl;
    }

};

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    while (root) {
        remove(root->val);//每次调用remove都会删除当前节点并更新root
    }
}

// 在以 node 为根的子树中插入值为 value 的节点。
// 若 node 为空，创建新节点并返回；
// 若 value 小于当前节点值，递归插入左子树；
// 若 value 大于当前节点值，递归插入右子树；
// 返回插入操作完成后该子树的根节点指针。

template<typename T>
TreeNode<T>* BinarySearchTree<T>::insertNode(TreeNode<T>* node, T value) {
    //若为空树，直接创建一个新的树节点并返回指向这个节点的指针
    if (node == NULL) {
        return new TreeNode<T>(value);
    }
    //若传入的值比当前树节点的值小，则递归调用插入左子树
    if (value < node->val) {
        node->left = insertNode(node->left, value);
    }
    //若传入的值比当前树节点的值大，则递归调用插入右子树
    else if (value > node->val) {
        node->right = insertNode(node->right, value);
    }
    //返回根节点
    return node;
}

// 若左右子树都不为空：
//   1. 在右子树中寻找值最小的节点（即中序后继）；
//   2. 用该节点的值覆盖当前节点；
//   3. 在右子树中递归删除该最小节点；
// 最后返回当前子树的根节点。
template<typename T>
TreeNode<T>* BinarySearchTree<T>::deleteNode(TreeNode<T>* node, T value) {
    //若树为空直接返回NULL，无法删除
    if (node == NULL) {
        return NULL;
    }
    //若传入的值小于当前树节点值，则递归调用在左子树删除
    if (value < node->val) {
        node->left = deleteNode(node->left, value);
    }
    //若传入的值大于当前树节点值，则递归调用在右子树删除
    else if (value > node->val) {
        node->right = deleteNode(node->right, value);
    }
    //传入值等于当前树节点值
    else {
        //若为叶子节点，直接删除，返回空树
        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL;
        }
        //若左子树为空，则保存右子树，删除当前节点，返回右子树
        else if (node->left == NULL) {
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        //若右子树为空，则保存左子树，删除当前节点，返回左子树
        else if (node->right == NULL) {
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        }
        //若左右子树都不为空，保存右子树，在右子树中找到值最小的树节点（右子树中最左的节点），将当前节点值更新为这个节点的值，然后将当前节点的右孩子指针指向调用deleteNode函数后的右子树
        else {
            TreeNode<T>* temp = node->right;
            while (temp->left) {
                temp = temp->left;
            }
            node->val = temp->val;
            node->right = deleteNode(node->right, node->val);
        }
    }
    return node;
}

// 在以 node 为根的子树中查找值为 value 的节点。
// 若当前节点为空，返回 false；
// 若 value 小于当前节点值，递归查找左子树；
// 若 value 大于当前节点值，递归查找右子树；
// 否则返回 true（找到）。
template<typename T>
bool BinarySearchTree<T>::searchNode(TreeNode<T>* node, T value) {
    if (node == NULL) {
        return false;
    }
    if (value < node->val) {
        return searchNode(node->left, value);
    }
    else if (value > node->val) {
        return searchNode(node->right, value);
    }
    return true;
}

// 对以 node 为根的子树进行中序遍历（左-根-右）。
// 对 BST 来说，中序遍历结果为递增序列。
template<typename T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* node) {
    if (node) {
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }
}

int main() {

    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(10);
    bst.insert(15);
    bst.insert(20);
    bst.insert(30);
    bst.insert(40);
    bst.insert(50);
    bst.insert(60);
    bst.inOrderTraversal();

    cout << bst.search(5) << endl;
    cout << bst.search(100) << endl;
    bst.remove(20);
    bst.inOrderTraversal();
    bst.insert(25);
    bst.insert(30);
    bst.insert(30);//重复值不会插入
    bst.inOrderTraversal();
    return 0;
}