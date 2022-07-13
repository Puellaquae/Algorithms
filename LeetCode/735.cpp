#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(const vector<int> &asteroids) {
        vector<int> ans;
        for (auto &a : asteroids) {
            bool insert = true;
            while (!ans.empty() && a < 0 && a * ans.back() < 0) {
                if (abs(a) == abs(ans.back())) {
                    ans.pop_back();
                    insert = false;
                    break;
                } else if (abs(a) > abs(ans.back())) {
                    ans.pop_back();
                } else {
                    insert = false;
                    break;
                }
            }
            if (insert) {
                ans.push_back(a);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    for (auto &v : s.asteroidCollision({5, 10, -5})) {
        cout << v << ",";
    }
    cout << endl;
    for (auto &v : s.asteroidCollision({8, -8})) {
        cout << v << ",";
    }
    cout << endl;
    for (auto &v : s.asteroidCollision({10, 2, -5})) {
        cout << v << ",";
    }
    cout << endl;
    for (auto &v : s.asteroidCollision({-2, -1, 1, 2})) {
        cout << v << ",";
    }
    cout << endl;
}