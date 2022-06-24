#include <deque>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> arrayChange(vector<int> &nums,
                            vector<vector<int>> &operations) {
        unordered_map<int, deque<int>> n2i;
        for (int i = 0; i < nums.size(); i++) {
            n2i[nums[i]].push_back(i);
        }
        for (auto &op : operations) {
            int idx = n2i[op[0]].front();
            n2i[op[0]].pop_front();
            nums[idx] = op[1];
            n2i[op[1]].push_back(idx);
        }
        return nums;
    }
};

void test(vector<int>&& v, vector<vector<int>>&& op) {
    Solution s;
    auto r = s.arrayChange(v, op);
    for (auto i : r) {
        cout << i << ", ";
    }
    cout << endl;
}

int main() { 
    test({1, 2, 4, 6}, {{1, 3}, {4, 7}, {6, 1}}); 
    test({1, 2}, {{1, 3}, {2, 1}, {3, 2}}); 
}