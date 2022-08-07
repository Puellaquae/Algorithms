#include <iostream>
#include <queue>

using namespace std;

class MedianFinder {
    priority_queue<int, deque<int>, less<>> little;
    priority_queue<int, deque<int>, greater<>> big;

public:
    /** initialize your data structure here. */
    MedianFinder() {}

    void addNum(int num) {
        if (little.empty()) {
            little.emplace(num);
        } else if (num <= little.top()) {
            little.emplace(num);
            if (little.size() - big.size() > 1) {
                big.emplace(little.top());
                little.pop();
            }
        } else {
            big.emplace(num);
            if (big.size() - little.size() > 1) {
                little.emplace(big.top());
                big.pop();
            }
        }
    }

    double findMedian() {
        if (little.size() == big.size()) {
            return (little.top() + big.top()) / 2.0;
        } else if (little.size() > big.size()) {
            return little.top();
        } else {
            return big.top();
        }
    }
};

int main() {
    MedianFinder m;
    m.addNum(1);
    cout << m.findMedian() << endl;
    m.addNum(2);
    cout << m.findMedian() << endl;
    m.addNum(3);
    cout << m.findMedian() << endl;
    m.addNum(4);
    cout << m.findMedian() << endl;
    m.addNum(5);
    cout << m.findMedian() << endl;
}