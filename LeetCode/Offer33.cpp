#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 1 2 3 5 6
    // 1 6 3 2 5
    // 1 3 2 6 5
    bool rebuildTree(const vector<int> &in, int l1, int h1,
                     const vector<int> &post, int l2, int h2) {
        // cout << l1 << ", " << h1 << "; " << l2 << ", " << h2 << "\n";
        if (h1 < l1 || h2 < l2) {
            return false;
        }
        if (h1 == l1 && h2 == l2) {
            return in[l1] == post[l2];
        }
        for (int i = h1; i >= l1; i--) {
            if (in[i] == post[h2]) {
                return (i == l1 || rebuildTree(in, l1, i - 1, post, l2,
                                               l2 + i - 1 - l1)) &&
                       (i == h1 ||
                        rebuildTree(in, i + 1, h1, post, l2 + i - l1, h2 - 1));
            }
        }
        return false;
    }

    bool verifyPostorder(const vector<int> &postorder) {
        if (postorder.empty()) {
            return true;
        }
        auto innerorder = postorder;
        sort(innerorder.begin(), innerorder.end());
        return rebuildTree(innerorder, 0, innerorder.size() - 1, postorder, 0,
                           postorder.size() - 1);
    }
};

int main() {
    Solution s;
    cout << s.verifyPostorder({1, 6, 3, 2, 5}) << endl;
    cout << s.verifyPostorder({1, 3, 2, 6, 5}) << endl;
    // 4 5 6 7
    // 4 6 7 5
    cout << s.verifyPostorder({4, 6, 7, 5}) << endl;
}