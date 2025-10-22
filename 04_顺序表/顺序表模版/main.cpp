/*
#include <iostream>
using namespace std;

#define eleType int

struct SequentialList {
    eleType *elements;
    int size;
    int capacity;
};

void initializeList(SequentialList *list, int capacity) {
    list->elements = new eleType[capacity];
    list->size = 0;
    list->capacity = capacity;
}

void destroyList(SequentialList *list) {
    delete[] list->elements;
}

int size(SequentialList *list) {
    return list->size;
}

bool isEmpty(SequentialList *list) {
    return list->size == 0;
}

void insert(SequentialList* list, int index, eleType element) {
    if (index < 0 || index > list->size) {
        throw invalid_argument("Invalid index");
    }
    if (list->size == list->capacity) {
        int newCapacity = list->capacity * 2;
        eleType* newElements = new eleType[newCapacity];
        for (int i = 0; i < list->size; ++i) {
            newElements[i] = list->elements[i];
        }
        delete[] list->elements;
        list->elements = newElements;
        list->capacity = newCapacity;
    }
    for (int i = list->size; i > index; --i) {
        list->elements[i] = list->elements[i - 1];
    }
    list->elements[index] = element;
    ++list->size;
}

void deleteElement(SequentialList *list, int index) {
    if (index < 0 || index >= list->size) {
        throw invalid_argument("Invalid index");
    }
    for (int i = index; i < list->size - 1; ++i) {
        list->elements[i] = list->elements[i + 1];
    }
    --list->size;
}

int findElement(SequentialList *list, eleType element) {
    for (int i = 0; i < list->size; ++i) {
        if (list->elements[i] == element) {
            return i;
        }
    }
    return -1;
}

eleType getElement(SequentialList *list, int index) {
    if (index < 0 || index >= list->size) {
        throw invalid_argument("Invalid index");
    }
    return list->elements[index];
}

void updateElement(SequentialList *list, int index, eleType value) {
    if (index < 0 || index >= list->size) {
        throw invalid_argument("Invalid index");
    }
    list->elements[index] = value;
}

int main() {
    SequentialList myList;
    initializeList(&myList, 10);
    for (int i = 0; i < 10; ++i) {
        insert(&myList, i, i * 10);
    }
    cout << "Size: " << size(&myList) << endl;
    cout << "Is empty: " << isEmpty(&myList) << endl;

    for (int i = 0; i < size(&myList); ++i) {
        cout << getElement(&myList, i) << " ";
    }
    cout << endl;
    deleteElement(&myList, 5);
    cout << "Size: " << size(&myList) << endl;
    updateElement(&myList, 1, 1314);
    for (int i = 0; i < size(&myList); ++i) {
        cout << getElement(&myList, i) << " ";
    }
    cout << endl;
    int idx = findElement(&myList, 20);
    updateElement(&myList, idx, 520);
    for (int i = 0; i < size(&myList); ++i) {
        cout << getElement(&myList, i) << " ";
    }
    cout << endl;
    destroyList(&myList);
    return 0;
}
*/
#include <iostream>
using namespace std;

//定义 这个顺序表中元素的类型为 int(指定一个类型)
#define eleType int

//定义顺序表，有三个成员变量，elements指向顺序表的首地址，size表示当前存了几个元素，capacity代表当前容量
struct SequentialList {
    eleType* elements;
    int size;
    int capacity;
};

//初始化顺序表，输入参数为指定顺序表首地址和容量，在堆上给这个顺序表申请大小为capacity个eleType的内存，初始化size为0，容量为输入的参数capacity
void initializeList(SequentialList* list, int capacity) {
    list->elements = new eleType[capacity];
    list->size = 0;
    list->capacity = capacity;
}

//销毁顺序表
void destroyList(SequentialList* list) {
    delete[] list->elements;
}

//返回顺序表的size
int size(SequentialList* list) {
    return list->size;
}

//判断顺序表是否为空
bool isEmpty(SequentialList* list) {
    return list->size == 0;
}

//插入操作
void insert(SequentialList* list, int index, int element) {
    //判断索引是否无效
    if (index < 0 || index > list->size) {
        throw invalid_argument("Invalid index");
    }
    //扩容
    if (list->size == list->capacity) {
        int newCapacity = list->capacity * 2;
        eleType* newElements = new eleType[newCapacity];
        for (int i = 0; i < list->size; ++i) {
            newElements[i] = list->elements[i];
        }
        delete[] list->elements;
        list->elements = newElements;
        list->capacity = newCapacity;
    }
    //插入
    for (int i = list->size; i > index; --i) {
            list->elements[i] = list->elements[i - 1];
    }
    list->elements[index] = element;
    ++list->size;
}

//删除index下标处的元素
void deleteList(SequentialList* list, int index) {
    if (index < 0 || index >= list->size) {
        throw invalid_argument("Invalid index");
    }
    for (int i = index; i < list->size - 1; ++i) {
        list->elements[i] = list->elements[i + 1];
    }
    --list->size;
}

//找到元素值为element的元素下标
int findElement(SequentialList* list, int element) {
    for (int i = 0; i < list->size - 1; ++i) {
        if (list->elements[i] == element) {
            return i;
        }
    }
    return -1;
}

//找到index下标对应的元素值
eleType getElement(SequentialList* list, int index) {
    if (index < 0 || index >= list->size) {
        throw invalid_argument("Invalid index");
    }
    return list->elements[index];
}

//更新index下标对应元素值为value
void updateElement(SequentialList* list, int index, eleType value) {
    if (index < 0 || index >= list->size) {
        throw invalid_argument("Invalid index");
    }
    list->elements[index] = value;
}

int main() {
    SequentialList myList;
    initializeList(&myList, 10);
    for (int i = 0; i < 10; ++i) {
        insert(&myList, i, i*100);
    }
    cout << "Size: " << myList.size << endl;
    cout << "Capacity: " << myList.capacity << endl;
    cout << "Is empty: " << isEmpty(&myList) << endl;
    for (int i = 0; i < myList.size; ++i) {
        cout << myList.elements[i] << " ";
    }
    cout << endl;

    deleteList(&myList, 5);
    updateElement(&myList, 1, 1314);

    int idx = findElement(&myList, 200);
    updateElement(&myList, idx, 520);

    cout << "Size: " << myList.size << endl;
    cout << "Capacity: " << myList.capacity << endl;
    cout << "Is empty: " << isEmpty(&myList) << endl;

    for (int i = 0; i < myList.size; ++i) {
        cout << myList.elements[i] << " ";
    }
    cout << endl;



    return 0;
}