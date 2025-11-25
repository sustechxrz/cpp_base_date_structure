#include <iostream>
using namespace std;

// ====================== 链表结点：存一条(key, value)记录 ======================
template<typename KeyType, typename ValueType>
class HashNode {
public:
    KeyType key;                  // 关键字
    ValueType value;              // 对应的值
    HashNode* next;               // 指向下一个结点（链地址法）

    // 构造函数：用给定的 key / value 初始化结点
    HashNode(const KeyType& key, const ValueType& value) {
        this->key = key;          // 拷贝构造 key
        this->value = value;      // 拷贝构造 value
        this->next = NULL;        // 链表指针先置空
    }
};

// ====================== 哈希表类定义 ======================
template<typename KeyType, typename ValueType>
class HashTable {
private:
    int size;                                   // 哈希表桶的数量
    HashNode<KeyType, ValueType>** table;       // 指针数组：每个位置指向一个链表的头结点

    // 哈希函数：把 key 映射到 [0, size-1]
    int hash(const KeyType& key) const {
        // 这里直接用 key % size，说明 KeyType 必须支持 % 运算
        int hashkey = key % size;
        if (hashkey < 0) hashkey += size;       // 防止负数
        return hashkey;
    }

public:
    HashTable(int size = 256);                  // 构造函数：申请空间并初始化
    ~HashTable();                               // 析构函数：释放所有结点和数组
    void insert(const KeyType& key, const ValueType& value);   // 插入或添加一条记录
    void remove(const KeyType& key);                            // 删除 key 对应的记录
    bool find(const KeyType& key, ValueType& value) const;      // 查找 key，对 value 赋值
};

// ====================== 构造函数：申请数组并清空 ======================
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int size) {
    this->size = size;
    // 申请一个指针数组，每个元素都是 HashNode*，一共 size 个桶
    table = new HashNode<KeyType, ValueType>*[size];
    // 初始化每个桶为 NULL（空链表）
    for (int i = 0; i < size; ++i) {
        table[i] = NULL;
    }
}

// ====================== 析构函数：逐桶释放所有链表，再释放数组 ======================
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    // 遍历每一个桶
    for (int i = 0; i < size; ++i) {
        if (table[i]) {
            HashNode<KeyType, ValueType>* current = table[i];
            // 释放该桶对应的完整链表
            while (current) {
                HashNode<KeyType, ValueType>* next = current->next;
                delete current;
                current = next;
            }
            table[i] = NULL;
        }
    }
    // 释放指针数组本身（注意这里应该是 delete[]）
    delete[] table;
    table = NULL;
}

// ====================== 插入：头插到对应桶的链表中 ======================
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    int index = hash(key);    // 计算 key 应该落到哪个桶
    // 创建一个新的结点，存放 (key, value)
    HashNode<KeyType, ValueType>* now = new HashNode<KeyType, ValueType>(key, value);
    // 如果这个桶原来是空的，直接把新结点放进去
    if (table[index] == NULL) {
        table[index] = now;
    } else {
        // 否则：采用头插法，新结点指向原来的头结点，再把桶指向新结点
        now->next = table[index];
        table[index] = now;
    }
}

// ====================== 删除：在对应桶的链表中删除 key ======================
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    int index = hash(key);        // 先算出落到哪个桶
    if (table[index]) {           // 该桶非空
        // 1. 先看第一个结点是不是要删的
        if (table[index]->key == key) {
            HashNode<KeyType, ValueType>* next = table[index]->next;
            delete table[index];
            table[index] = next;  // 桶指针跳过被删结点
        } else {
            // 2. 否则在链表中向后找：current 指向“前一个结点”
            HashNode<KeyType, ValueType>* current = table[index];
            while (current->next && current->next->key != key) {
                current = current->next;
            }
            // 找到了 current->next 就是要删的结点
            if (current->next) {
                HashNode<KeyType, ValueType>* next = current->next->next;
                delete current->next;
                current->next = next;  // 从链表中断开
            }
        }
    }
}

// ====================== 查找：在对应桶的链表中查找 key ======================
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::find(const KeyType& key, ValueType& value) const {
    int index = hash(key);        // 计算桶下标
    if (table[index]) {
        // 1. 先看链表第一个结点是不是要找的
        if (table[index]->key == key) {
            value = table[index]->value;
            return true;
        } else {
            // 2. 否则在链表中继续找
            HashNode<KeyType, ValueType>* current = table[index];
            // current->next 还存在且 key 不相等就继续往后
            while (current->next && current->next->key != key) {
                current = current->next;
            }
            // 如果 current->next 存在，说明找到了
            if (current->next) {
                value = current->next->value;
                return true;
            }
        }
    }
    // 没找到
    return false;
}

// ====================== 简单测试 ======================
int main() {
    // 创建一个 Key 为 int，Value 为 char 的哈希表，大小 1000
    HashTable<int, char> h(1000);
    // 插入几条记录
    h.insert(1, 'a');
    h.insert(2, 'b');
    h.insert(3, 'c');
    h.insert(4, 'd');
    h.insert(5103745, 'e');

    char val;

    // 查找 key = 5，不存在
    if (!h.find(5, val)) {
        cout << "5 not found" << endl;
    }

    // 查找 key = 5103745，存在
    if (h.find(5103745, val)) {
        cout << "5103745 found, value = " << val << endl;
    }

    return 0;
}
