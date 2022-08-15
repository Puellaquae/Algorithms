#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int edgeScore(const vector<int>& edges) {
        map<int, long long> a;
        long long ans = 0;
        for (int i = 0; i < edges.size(); i++) {
            a[edges[i]] += i;
            ans = max(ans, a[edges[i]]);
        }
        for (auto& kv: a) {
            if (kv.second == ans) {
                return kv.first;
            }
        }
        return 0;
    }
};