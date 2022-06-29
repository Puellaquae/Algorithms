#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> p;
        for (int j = 0; j <= rowIndex; j++) {
            vector<int> l(j + 1, 1);
            for (int i = 1; i < j; i++) {
                l[i] = p[i - 1] + p[i];
            }
            p = l;
        }
        return p;
    }
};

void test(int n) {
    auto res = Solution{}.getRow(n);
    for (const auto &v : res) {
        cout << v << ", ";
    }
    cout << endl;
}

int main() {
    test(6);
    test(1);
    test(3);
}