#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for (int j = 0; j < numRows; j++) {
            vector<int> l(j + 1, 1);
            for (int i = 1; i < j; i++) {
                l[i] = res[j - 1][i - 1] + res[j - 1][i];
            }
            res.push_back(l);
        }
        return res;
    }
};

void test(int n) {
    auto res = Solution{}.generate(n);
    for (const auto &v : res) {
        for (const auto &n : v) {
            cout << n << ", ";
        }
        cout << endl;
    }
}

int main() { 
    test(6); 
    test(1); 
}