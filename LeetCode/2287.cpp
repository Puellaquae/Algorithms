#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int rearrangeCharacters(string s, string target) {
        unordered_map<char, int> cs, ts;
        for (char c : s) {
            cs[c]++;
        }
        for (char t: target) {
            ts[t]++;
        }
        int max = s.size();
        for (auto& p : ts) {
            max = min(max, cs[p.first] / p.second);
        }
        return max;
    }
};

int main() {
    Solution s;
    cout << s.rearrangeCharacters("ilovecodingonleetcode", "code") << endl;
    cout << s.rearrangeCharacters("abcba", "abc") << endl;
    cout << s.rearrangeCharacters("abbaccaddaeea", "aaaaa") << endl;
}