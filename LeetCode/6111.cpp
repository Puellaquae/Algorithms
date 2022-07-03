#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *head) {
        vector<vector<int>> ans(m, vector<int>(n, -1));
        int py = 0, px = 0;
        int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int cd = 0;
        int bd[4] = {0, 0, 0, 0};
        while (head != nullptr) {
            cout << "[" << py << "][" << px << "]\n";
            ans[py][px] = head->val;
            head = head->next;
            py += dir[cd][0];
            px += dir[cd][1];
            int tt = 4;
            while (!(bd[0] <= py && py < m - bd[2] && bd[3] <= px && px < n - bd[1]) &&
                   tt >= 0) {
                tt--;
                py -= dir[cd][0];
                px -= dir[cd][1];
                bd[cd]++;
                cd = (cd + 1) % 4;
                py += dir[cd][0];
                px += dir[cd][1];
            }
            if (tt < 0) {
                break;
            }
        }
        return ans;
    }
};

void test(int _m, int _n, const vector<int> &v) {
    Solution s;
    ListNode *n;
    ListNode **pn = &n;
    for (auto i : v) {
        *pn = new ListNode(i);
        pn = &((*pn)->next);
    }
    auto x = s.spiralMatrix(_m, _n, n);
    for (auto &l : x) {
        for (auto &i : l) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main() { 
    test(3, 5, {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0}); 
    test(1, 4, {0, 1, 2}); 
}