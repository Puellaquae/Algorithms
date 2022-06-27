#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    bool isPQ(vector<vector<int>> &mem,const string& s, int i, int j) {
        if (i >= j) {
            return true;
        }
        if (mem[i][j] != -1) {
            return mem[i][j] == 1;
        }
        bool res = false;
        if (s[i] == s[j]) {
            res = isPQ(mem, s, i + 1, j - 1);
            
        }
        mem[i][j] = res;
        return res;
    }

    string longestPalindrome(string s) {
        int n = s.size();
        int maxL = 0;
        int maxI, maxJ;
        vector<vector<int>> mem(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPQ(mem, s, i, j)) {
                    if (j - i + 1 > maxL) {
                        maxL = j - i + 1;
                        maxJ = j;
                        maxI = i;
                    }
                }
            }
        }
        return s.substr(maxI, maxL);
    }
};

int main() {
    Solution s;
    cout << s.longestPalindrome("babad") << endl;
    cout << s.longestPalindrome("cbbd") << endl;
    cout << s.longestPalindrome("a") << endl;
}