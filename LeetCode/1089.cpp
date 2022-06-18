#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

class Solution {
public:
    void duplicateZeros(vector<int> &arr) {
        int ridx = 0, cidx = 0, n = arr.size();
        for (; ridx < n; ridx++) {
            cidx += (arr[ridx] == 0 ? 2 : 1);
        }
        for (ridx--, cidx--; ridx >= 0; ridx--) {
            if (arr[ridx] == 0) {
                if (cidx < n) {
                    arr[cidx] = arr[ridx];
                }
                cidx--;
            }
            if (cidx < n) {
                arr[cidx] = arr[ridx];
            }
            cidx--;
        }
    }
};

int main() {
    Solution solution;
    auto test = [&solution](vector<int> &&v) {
        solution.duplicateZeros(v);
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
        cout << endl;
    };

    test({1, 0});
    test({1, 0, 2, 3, 0, 4, 5, 0});
    test({1, 2, 3});
    test({1, 0, 2, 3, 0, 4, 5, 0});
    test({8, 4, 5, 0, 0, 0, 0, 7});
}