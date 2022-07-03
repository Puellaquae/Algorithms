#include <iostream>
#include <array>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        string res = "";
        while (num >= 1000) {
            num -= 1000;
            res += "M";
        }
        res += (array<string, 10>{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}[num / 100 % 10]);
        num %= 100;
        res += (array<string, 10>{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"}[num / 10 % 10]);
        num %= 10;
        res += (array<string, 10>{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}[num % 10]);
        return res;
    }
};

int main() {
    Solution s;
    cout << s.intToRoman(3) << endl;
    cout << s.intToRoman(4) << endl;
    cout << s.intToRoman(9) << endl;
    cout << s.intToRoman(58) << endl;
    cout << s.intToRoman(1994) << endl;
}