#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maxEqualFreq(const vector<int> &nums) {
        unordered_map<int, int> m;
        unordered_map<int, int> cm;
        int l = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (m.count(nums[i]) != 0) {
                cm[m[nums[i]]]--;
                if (cm[m[nums[i]]] == 0) {
                    cm.erase(m[nums[i]]);
                }
            }
            m[nums[i]]++;
            cm[m[nums[i]]]++;
            if (cm.size() == 2) {
                auto p = cm.begin();
                int a = p->first;
                int av = p->second;
                ++p;
                int b = p->first;
                int bv = p->second;
                if (bv > av) {
                    swap(a, b);
                    swap(av, bv);
                }
                if ((av == 1 || bv == 1) && (a == b - 1 || b == 1)) {
                    l = i + 1;
                }
            } else if (cm.size() == 1) {
                if (cm.begin()->first == 1 || m.size() == 1) {
                    l = i + 1;
                }
            }
        }
        return l;
    }
};

int main() {
    Solution s;
    cout << s.maxEqualFreq({2, 2, 1, 1, 5, 3, 3, 5}) << endl;
    cout << s.maxEqualFreq({1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}) << endl;
    cout << s.maxEqualFreq({10, 2, 8, 9, 3, 8, 1, 5, 2, 3, 7, 6}) << endl;
    cout << s.maxEqualFreq({1, 1, 1, 2, 2}) << endl;
    cout << s.maxEqualFreq({1, 2}) << endl;
    cout << s.maxEqualFreq({1, 1}) << endl;
    cout << s.maxEqualFreq({1, 1, 1, 2, 2, 2, 3, 3, 3}) << endl;
}