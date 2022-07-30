#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool validSquare(const vector<int>& p1, const vector<int>& p2, const vector<int>& p3, const vector<int>& p4) {
        auto dot = [](const pair<int, int>& a, const pair<int, int>& b) -> int {
            return a.first * b.first + a.second * b.second;
        };
        auto v12 = make_pair(p2[0] - p1[0], p2[1] - p1[1]);
        auto v13 = make_pair(p3[0] - p1[0], p3[1] - p1[1]);
        auto v14 = make_pair(p4[0] - p1[0], p4[1] - p1[1]);
        if (dot(v12, v13) == 0) {
            return v12 != v13 && dot(v12, v12) == dot(v13, v13) && p3[0] + v12.first == p4[0] && p3[1] + v12.second == p4[1];
        } else if (dot(v12, v14) == 0) {
            return v12 != v14 && dot(v12, v12) == dot(v14, v14) && p4[0] + v12.first == p3[0] && p4[1] + v12.second == p3[1];
        } else if (dot(v13, v14) == 0) {
            return v14 != v13 && dot(v14, v14) == dot(v13, v13) && p4[0] + v13.first == p2[0] && p4[1] + v13.second == p2[1];
        }
        return false;
    }
};

int main() {
    Solution s;
    cout << s.validSquare({0, 0}, {1, 1}, {1, 0}, {0, 1}) << endl;
    cout << s.validSquare({0, 0}, {1, 1}, {1, 0}, {0, 12}) << endl;
    cout << s.validSquare({1, 0}, {-1, 0}, {0, 1}, {0, -1}) << endl;
}