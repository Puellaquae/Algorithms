#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res;
        res.push_back(0);
        int i = 0;
        while (i < n) {
            int len = res.size();
            for (int j = 0; j < len && i < n; j++, i++) {
                res.push_back(res[j] + 1);
            }
        }
        return res;
    }
};

void test(int n) {
    auto res = Solution{}.countBits(n);
    for (auto &v : res) {
        cout << v << ", ";
    }
    cout << endl;
}

int main() {
    test(2);
    test(5);
}