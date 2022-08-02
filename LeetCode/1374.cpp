#include <iostream>
using namespace std;

class Solution {
public:
    string generateTheString(int n) {
        int i = 0;
        string ans = "";
        for (int i = 0; i < ((n % 2 == 0) ? (n - 1) : n); i++) {
            ans += "a";
        }
        if (n % 2 == 0) {
            ans += "b";
        }
        return ans;
    }
};