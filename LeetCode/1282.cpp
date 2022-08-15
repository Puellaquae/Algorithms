#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        map<int, vector<int>> g;
        for (int i = 0; i < groupSizes.size(); i++) {
            g[groupSizes[i]].push_back(i);
        }
        vector<vector<int>> ans;
        for (auto& kv: g) {
            vector<int> xx;
            for (int i = 0; i < kv.second.size() / kv.first; i++) {
                xx.assign(kv.second.begin() + i * kv.first, kv.second.begin() + (i + 1) * kv.first);
                ans.push_back(xx);
                xx.clear();
            }
        }
        return ans;
    }
};