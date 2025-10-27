#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node *next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node *head;
    int size;
public:
    Stack() : head(nullptr), size(0) {}
    ~Stack();
    void push(T d);
    T pop();
    T top() const;
    int getsize() const;
};

template <typename T>
Stack<T>::~Stack() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void Stack<T>::push(T d) {
    Node* newNode = new Node(d);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
T Stack<T>::pop() {
    if (head == NULL) {
        throw underflow_error("Stack is empty");
    }
    T result = head->data;
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
    return result;
}

template<typename T>
T Stack<T>::top() const {
    if (head == NULL) {
        throw underflow_error("Stack is empty");
    }
    return head->data;
}

template<typename T>
int Stack<T>::getsize() const {
    return size;
}

int main() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    cout << s.top() << endl;
    cout << s.getsize() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.getsize() << endl;
    return 0;
}