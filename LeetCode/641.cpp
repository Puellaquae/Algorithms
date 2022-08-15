#include <iostream>
using namespace std;

class MyCircularDeque {
    int *data = nullptr;
    int front = 0;
    int back = 1;
    int len = 0;
    int cap = 0;
    int size = 0;

public:
    MyCircularDeque(int k) {
        data = new int[k + 1];
        cap = k;
        len = k + 1;
    }

    bool insertFront(int value) {
        if (isFull()) {
            return false;
        }
        data[front] = value;
        front = (front - 1 + len) % len;
        size++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        data[back] = value;
        back = (back + 1) % len;
        size++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        front = (front + 1) % len;
        size--;
        return true;
    }

    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        back = (back - 1 + len) % len;
        size--;
        return true;
    }

    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return data[(front + 1) % len];
    }

    int getRear() {
        if (isEmpty()) {
            return -1;
        }
        return data[(back - 1 + len) % len];
    }

    bool isEmpty() { return size == 0; }

    bool isFull() { return size == cap; }
};