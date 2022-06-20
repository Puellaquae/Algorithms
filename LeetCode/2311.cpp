#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int longestSubsequence(string s, int k) {
        vector<int> one;
        int n = 0;
        int c = 0;
        int b = 0;
        bool o = false;
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            if (*it == '1' && !o) {
                if (n >= 32) {
                    o = true;
                } else {
                    if (c + (1LL << n) <= k) {
                        c += (1LL << n);
                    } else {
                        o = true;
                    }
                }
            }
            if (!o || *it == '0') {
                b++;
            }
            n++;
        }
        return b;
    }
};

int main() {
    Solution s;
    cout << s.longestSubsequence("00101001", 1) << endl;
    cout << s.longestSubsequence("1001010", 5) << endl;
    cout << s.longestSubsequence(
                "00010101001101100101110111100011111110000101100000010001000011"
                "11000000111110010001111001111010011110010111010010110111010010"
                "11011001111111010011100011110111010000010000010111001001111101"
                "100001111",
                300429827)
         << endl;
    cout << s.longestSubsequence(
                "00010101001101100101110111100011111110000101100000010001000011"
                "11000000111110010001111001111010011110010111010010110111010010"
                "00000000000000000000000000000000000000000000000000000000000000"
                "00000000000",
                1)
         << endl;
}