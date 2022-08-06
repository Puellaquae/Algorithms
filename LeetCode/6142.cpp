#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    long long countBadPairs2(const vector<int> &nums) {
        long long cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (j - i != nums[j] - nums[i]) {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    long long countBadPairs(const vector<int> &nums) {
        map<int, int> ns;
        for (int i = 0; i < nums.size(); i++) {
            ns[nums[i] - i]++;
        }
        long long n = nums.size();
        long long cnt = n * (n - 1) / 2;
        for (auto &kv : ns) {
            long long c = kv.second;
            cnt -= c * (c - 1) / 2;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    cout << s.countBadPairs({4, 1, 3, 3}) << endl;
    cout << s.countBadPairs({1, 4, 3, 3}) << endl;
    cout << s.countBadPairs({1, 2, 3, 4, 5}) << endl;
}