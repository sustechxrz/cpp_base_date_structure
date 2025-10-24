#include <iostream>
#include <stdexcept>
using namespace std;

#define eleType int

struct ListNode {
    eleType data;
    ListNode *next;

    ListNode(eleType x) : data(x), next(NULL) {}
};

class LinkedList {
private:
    ListNode *head;
    int size;

public:
    LinkedList() : head(NULL), size(0) {}
    ~LinkedList();
    void insert(int i, eleType value);
    void remove(int i);
    ListNode* find(eleType value);
    ListNode* get(int i);
    void update(int i, eleType value);
    void print();
};

LinkedList::~LinkedList() {
    ListNode *curr = head;
    while (curr != NULL) {
        ListNode *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}

void LinkedList::insert(int i, eleType value) {
    if (i < 0 || i > size) {
        throw out_of_range("Invalid position");
    }
    ListNode *newNode = new ListNode(value);
    if (i == 0) {
        newNode->next = head;
        head = newNode;
    }
    else {
        ListNode *curr = head;
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    ++size;
}

void LinkedList::remove(int i) {
    if (i < 0 || i >= size) {
        throw out_of_range("Invalid position");
    }
    if (i == 0) {
        ListNode *tmp = head;
        head = head->next;
        delete tmp;
    }
    else {
        ListNode *curr = head;
        for (int j = 0; j < i - 1; ++j) {
            curr = curr->next;
        }
        ListNode *tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
    }
    --size;
}

ListNode* LinkedList::find(eleType value) {
    ListNode *curr = head;
    while (curr != NULL && curr->data != value) {
        curr = curr->next;
    }
    return curr;
}

ListNode* LinkedList::get(int i) {
    if (i < 0 || i >= size) {
        throw out_of_range("Invalid position");
    }
    ListNode *curr = head;
    for (int j = 0; j < i ; ++j) {
        curr = curr->next;
    }
    return curr;
}

void LinkedList::update(int i, eleType value) {
    get(i)->data = value;
}

void LinkedList::print() {
    ListNode *curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    LinkedList myList;
    myList.insert(0, 1);
    myList.insert(1, 2);
    myList.insert(2, 3);
    myList.insert(3, 4);
    myList.insert(4, 5);
    myList.print();
    myList.remove(0);
    myList.print();
    cout << myList.find(2)->data << endl;
    cout << myList.get(2)->data << endl;
    myList.update(1,10);
    myList.print();
    ;

    return 0;
}