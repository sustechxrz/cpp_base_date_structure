#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node *next;
        Node(T d) : data(d), next(NULL){}
    };
    Node *head;
    int size;
public:
    Stack() : head(NULL), size(0) {}
    ~Stack();
    void push(T element);
    T pop();
    T top() const;
    int getSize() const;
    bool empty() const;
};

template<typename T>
Stack<T>::~Stack() {
    while (head) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void Stack<T>::push(T element) {
    Node *newNode = new Node(element);
    newNode->next = head;
    head = newNode;
    ++size;
}

template<typename T>
T Stack<T>::pop() {
    if (head == NULL) {
        throw overflow_error("Stack is empty");
    }
    T ans = head->data;
    Node* temp = head;
    head = head->next;
    delete temp;
    --size;
    return ans;
}

template<typename T>
T Stack<T>::top() const {
    if (head == NULL) {
        throw underflow_error("Stack is empty");
    }
    return head->data;
}

template<typename T>
int Stack<T>::getSize() const {
    return size;
}

template<typename T>
bool Stack<T>::empty() const {
    return size == 0;
}

class MyQueue {
private:
    Stack<int> s1;
    Stack<int> s2;
public:
    MyQueue() {}
    void push(int element) {
        s1.push(element);
    }
    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.pop());
            }
        }
        return s2.pop();
    }
    int peek() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.pop());
            }
        }
        return s2.top();
    }
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

int main() {

    return 0;
}