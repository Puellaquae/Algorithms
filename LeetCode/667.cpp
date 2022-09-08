#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<bool> used(n, false);
        vector<int> ans;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int dif = i < (n - k) ? 1 : (n - i);
            used[cur] = true;;
            if (cur + dif <= n && !used[cur + dif]) {
                ans.push_back(cur + dif);
                cur += dif;
            } else {
                ans.push_back(cur - dif);
                cur -= dif;
            }
        }
        return ans;
    }
};

int main() {
    for(auto v: Solution{}.constructArray(5, 2)) {
        cout << v << ", ";
    }
    cout << endl;
}