#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string reorderSpaces(string text) {
        int spaces = 0;
        string buf;
        vector<string> words;
        for (auto c : text) {
            if (c == ' ') {
                if (!buf.empty()) {
                    words.emplace_back(buf);
                    buf.clear();
                }
                spaces++;
            } else {
                buf.push_back(c);
            }
        }
        if (!buf.empty()) {
            words.emplace_back(buf);
        }
        int spilt, endding;
        if (words.size() == 1) {
            endding = spaces;
        } else {
            spilt = spaces / (words.size() - 1);
            endding = spaces % (words.size() - 1);
        }
        string ans;
        bool first = true;
        for (auto &word : words) {
            if (!first) {
                for (int i = 0; i < spilt; i++) {
                    ans.push_back(' ');
                }
            }
            first = false;
            ans += word;
        }
        for (int i = 0; i < endding; i++) {
            ans.push_back(' ');
        }
        return ans;
    }
};