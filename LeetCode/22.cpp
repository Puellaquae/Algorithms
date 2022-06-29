#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void dfs(vector<string>& res, string s, int l, int rl, int rr) {
        if (rr == 0 && rl == 0) {
            res.push_back(s);
        } else {
            if (l > 0 && rr > 0){
                dfs(res, s + ")", l - 1, rl, rr - 1);
            }
            if (rl > 0) {
                dfs(res, s + "(", l + 1, rl - 1, rr);
            }
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs(res, "", 0, n, n);
        return res;
    }
};

int main() {
    Solution s;
    for (auto&& r: s.generateParenthesis(3)) {
        cout << r << endl;
    }
    for (auto&& r: s.generateParenthesis(1)) {
        cout << r << endl;
    }
}