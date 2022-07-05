#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int> &arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> ans;
        int minD = arr[1] - arr[0];
        for (int i = 0; i < arr.size() - 1; i++) {
            int d = arr[i + 1] - arr[i];
            if (d < minD) {
                minD = d;
                ans.clear();
                ans.push_back({arr[i], arr[i + 1]});
            } else if (d == minD) {
                ans.push_back({arr[i], arr[i + 1]});
            }
        }
        return ans;
    }
};

void test(vector<int> &&arr) {
    for (auto &p : Solution{}.minimumAbsDifference(arr)) {
        cout << "[" << p[0] << ", " << p[1] << "], ";
    }
    cout << endl;
}

int main() {
    test({4, 2, 1, 3});
    test({1, 3, 6, 10, 15});
    test({3, 8, -10, 23, 19, -4, -14, 27});
    test({40, 11, 26, 27, -20});
}