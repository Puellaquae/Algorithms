#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string greatestLetter(string s) {
        vector<int> l(26, 0);
        vector<int> u(26, 0);
        for (char c : s) {
            if ('a' <= c && c <= 'z') {
                l[c - 'a']++;
            } else if ('A' <= c && c <= 'Z') {
                u[c - 'A']++;
            }
        }
        string res = "";
        for (int i = 25; i >= 0; i--) {
            if (l[i] > 0 && u[i] > 0) {
                res.push_back('A' + i);
                return res;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.greatestLetter("lEeTcOdE") << endl;
    cout << s.greatestLetter("arRAzFif") << endl;
    cout << s.greatestLetter("AbCdEfGhIjK") << endl;
}