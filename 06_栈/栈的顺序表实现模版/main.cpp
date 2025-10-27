#include <iostream>
#include<stdexcept>
using namespace std;

template<typename T>
class Stack {
private:
    T* data;
    int size;
    int capacity;
    void resize();
public:
    Stack() : data(new T[10]), size(0), capacity(10) {}
    ~Stack();
    void push(T element);
    T pop();
    T top() const;
    int getsize() const;

};

template<typename T>
void Stack<T>::resize() {
    int newCapacity = 2 * capacity;
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
Stack<T>::~Stack() {
    delete[] data;
}

template<typename T>
void Stack<T>::push(T element) {
    if (size == capacity) {
        resize();
    }
    data[size++] = element;
}

template<typename T>
T Stack<T>::pop() {
    if (size == 0) {
        throw underflow_error("Stack is empty");
    }
    return data[--size];
}

template<typename T>
T Stack<T>::top() const {
    if (size == 0) {
        throw underflow_error("Stack is empty");
    }
    return data[size - 1];
}

template<typename T>
int Stack<T>::getsize() const {
    return size;
}

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(7);
    stack.push(10);
    cout << stack.top() << endl;
    stack.push(100);
    cout << stack.top() << endl;
    stack.pop();
    stack.pop();
    cout << stack.top() << endl;
    cout << stack.getsize() << endl;
    return 0;
}