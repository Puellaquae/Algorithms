#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>> &&costs) {
        int n = costs.size();
        for (int i = 1; i < n; ++i) {
            costs[i][0] += min(costs[i - 1][1], costs[i - 1][2]);
            costs[i][1] += min(costs[i - 1][0], costs[i - 1][2]);
            costs[i][2] += min(costs[i - 1][1], costs[i - 1][0]);
        }
        return *min_element(costs.back().begin(), costs.back().end());
    }
};

int main() {
    Solution s;
    cout << s.minCost({{17, 2, 17}, {16, 16, 5}, {14, 3, 19}}) << endl;
    cout << s.minCost({{7, 6, 2}}) << endl;
    cout << s.minCost({{15, 1, 8},   {1, 18, 10},  {13, 18, 18}, {14, 7, 3},
                       {12, 11, 16}, {18, 13, 19}, {7, 8, 15},   {13, 7, 18},
                       {3, 17, 11},  {20, 17, 12}, {8, 5, 6},    {11, 2, 7},
                       {2, 18, 8},   {18, 12, 8},  {19, 10, 6},  {13, 1, 10},
                       {7, 8, 7},    {6, 4, 11},   {11, 13, 6},  {19, 14, 15},
                       {17, 8, 17},  {13, 10, 17}, {17, 15, 5},  {12, 5, 20},
                       {15, 9, 11},  {20, 17, 15}, {3, 2, 16},   {14, 11, 18},
                       {20, 15, 18}, {18, 2, 17}})
         << endl;
}