#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    T* data;
    int front;
    int rear;
    int capacity;
    void resize();
public:
    Queue() : data(new T[10]),front(0),rear(0),capacity(10){}
    ~Queue() ;
    void enqueue(T element);
    T dequeue();
    T getFront() const;
    int getsize() const;
};

template <typename T>
void Queue<T>::resize() {
    T* newData = new T[2*capacity];
    for (int i = 0; i < capacity; i++) {
            newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity *= 2;
}

template <typename T>
Queue<T>::~Queue() {
    delete[] data;
}

template <typename T>
void Queue<T>::enqueue(T element) {
    if (rear == capacity ) {
        resize();
    }
    data[rear++] = element;
}

template <typename T>
T Queue<T>::dequeue() {
    if (front == rear) {
        throw underflow_error("Queue is empty");
    }
    return data[front++];
}

template <typename T>
T Queue<T>::getFront() const {
    if (front == rear) {
        throw underflow_error("Queue is empty");
    }
    return data[front];
}

template <typename T>
int Queue<T>::getsize() const {
    return rear - front;
}


int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << q.getsize() << endl;
    cout << q.getFront() << endl;
    cout << q.dequeue() << endl;
    cout << q.getFront() << endl;
    cout << q.getsize() << endl;
    return 0;
}