#include <vector>
#include <iostream>

using namespace std;

class MyCircularQueue {
    vector<int> data;
    int write = 0;
    int read = 0;
    int cap;
    int size = 0;
public:
    MyCircularQueue(int k) : data(k, 0), cap(k) {

    }
    
    bool enQueue(int value) {
        if (!isFull()) {
            data[write] = value;
            write = (write + 1) % cap;
            size++;
            return true;
        }
        return false;
    }
    
    bool deQueue() {
        if (!isEmpty()) {
            read = (read + 1) % cap;
            size--;
            return true;
        }
        return false;
    }
    
    int Front() {
        if (!isEmpty()) {
            return data[read];
        }
        return -1;
    }
    
    int Rear() {
        if (!isEmpty()) {
            return data[(write - 1 + cap) % cap];
        }
        return -1;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == cap;
    }
};

int main() {
    MyCircularQueue q(3);
    cout << q.enQueue(1) << endl;
    cout << q.enQueue(2) << endl;
    cout << q.enQueue(3) << endl;
    cout << q.enQueue(4) << endl;
    cout << q.Rear() << endl;
    cout << q.isFull() << endl;
    cout << q.deQueue() << endl;
    cout << q.enQueue(4) << endl;
    cout << q.Rear() << endl;
}