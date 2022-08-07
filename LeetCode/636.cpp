#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> exclusiveTime(int n, const vector<string> &logs) {
        vector<pair<int, int>> s;
        vector<int> ts(n, 0);
        for (const auto &str : logs) {
            int idx;
            int time;
            char status[10];
            sscanf(str.c_str(), "%d:%[^:]:%d", &idx, status, &time);
            if (status[0] == 's') {
                s.emplace_back(idx, time);
            } else {
                if (s.back().first == idx) {
                    int t = time - s.back().second + 1;
                    s.pop_back();
                    ts[idx] += t;
                    for (auto &p : s) {
                        p.second += t;
                    }
                }
            }
        }
        return ts;
    }
};

int main() {
    Solution s;
    for (auto v : s.exclusiveTime(2, {"0:start:0", "0:start:2", "0:end:5",
                                      "1:start:6", "1:end:6", "0:end:7"})) {
        cout << v << ", ";
    }
    cout << endl;
    for (auto v : s.exclusiveTime(1, {"0:start:0", "0:start:2", "0:end:5",
                                      "0:start:6", "0:end:6", "0:end:7"})) {
        cout << v << ", ";
    }
    cout << endl;
    for (auto v : s.exclusiveTime(2, {"0:start:0", "0:start:2", "0:end:5",
                                      "1:start:7", "1:end:7", "0:end:8"})) {
        cout << v << ", ";
    }
    cout << endl;
    for (auto v : s.exclusiveTime(1, {"0:start:0", "0:start:1", "0:start:2",
                                      "0:end:3", "0:end:4", "0:end:5"})) {
        cout << v << ", ";
    }
    cout << endl;
}
