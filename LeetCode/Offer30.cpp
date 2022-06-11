// Also LeetCode 155

#include <iostream>
#include <vector>
using namespace std;

class MinStack {
    vector<pair<int, int>> stack;

public:
    /** initialize your data structure here. */
    MinStack() {}

    void push(int x) {
        if (stack.empty()) {
            stack.emplace_back(x, x);
        } else {
            int lastMin = min();
            stack.emplace_back(x, lastMin < x ? lastMin : x);
        }
    }

    void pop() { stack.pop_back(); }

    int top() { return stack.back().first; }

    int min() { return stack.back().second; }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */

int main() {
    MinStack stack;
    stack.push(-2);
    stack.push(0);
    stack.push(-3);
    cout << stack.min() << "\n";
    stack.pop();
    cout << stack.top() << "\n";
    cout << stack.min() << "\n";
}