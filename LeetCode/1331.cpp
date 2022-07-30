#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> arrayRankTransform(const vector<int> &arr) {
        auto arrC = arr;
        sort(arrC.begin(), arrC.end());
        arrC.erase(unique(arrC.begin(), arrC.end()), arrC.end());
        map<int, int> v2i;
        for (int i = 0; i < arrC.size(); i++) {
            v2i[arrC[i]] = i + 1;
        }
        vector<int> ans;
        for (auto &v : arr) {
            ans.push_back(v2i[v]);
        }
        return ans;
    }
};