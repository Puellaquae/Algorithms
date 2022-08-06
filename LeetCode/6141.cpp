#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        map<int, int> ws;
        for (auto& vw: items1) {
            ws[vw[0]] += vw[1];
        }
        for (auto& vw: items2) {
            ws[vw[0]] += vw[1];
        }
        vector<vector<int>> ans;
        for (auto& kv: ws) {
            ans.push_back({kv.first, kv.second});
        }
        return ans;
    }
};