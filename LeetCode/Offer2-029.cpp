#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    Node *next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node *_next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node *insert(Node *head, int insertVal) {
        if (head == nullptr) {
            Node *node = new Node(insertVal);
            node->next = node;
            return node;
        }
        Node *maxHead = head;
        Node *searchHead = head;
        do {
            if (searchHead->val >= maxHead->val) {
                maxHead = searchHead;
            }
            searchHead = searchHead->next;
        } while (searchHead != head);
        Node **place = &maxHead->next;
        while ((*place)->val <= insertVal) {
            place = &(*place)->next;
            if (*place == maxHead->next) {
                break;
            }
        }
        *place = new Node(insertVal, *place);
        return head;
    }
};

void test(vector<int> &&vals, int insert) {
    Node *head = nullptr;
    Node **cur = &head;
    for (int val : vals) {
        *cur = new Node(val);
        cur = &(*cur)->next;
    }
    *cur = head;
    Solution solution;
    head = solution.insert(head, insert);
    cur = &head;
    do {
        cout << (*cur)->val << ", ";
        cur = &(*cur)->next;
    } while (*cur != head);
    cout << endl;
}

int main() {
    test({}, 1);
    test({1}, 0);
    test({3, 4, 1}, 2);
    test({1, 3, 5}, 0);
    test({1, 3, 5}, 4);
    test({1, 3, 5}, 6);
    test({1, 3, 5}, 2);
    test({1, 3, 3}, 4);
    test({1, 3, 3}, 3);
}