#include <iostream>
#include <map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        map<Node*, Node*> ref;
        Node *outHead = nullptr;
        Node **out = &outHead;
        Node *cur = head;
        while (cur != nullptr) {
            *out = new Node(cur->val);
            ref[cur] = *out;
            out = &((*out)->next);
            cur = cur->next;
        }
        cur = head;
        Node* outCur = outHead;
        while (cur != nullptr) {
            outCur->random = ref[cur->random];
            outCur = outCur->next;
            cur = cur->next;
        }
        return outHead;
    }
};