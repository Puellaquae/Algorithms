#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    vector<int> reversePrint(ListNode *head) {
        ListNode* cur = head;
        vector<int> data;
        while (cur != nullptr) {
            data.push_back(cur->val);
            cur = cur->next;
        }
        reverse(data.begin(), data.end());
        return data;
    }
};