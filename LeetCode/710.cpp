#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
    unordered_map<int, int> b2w;
    int wS;
    int wCI = 0;
public:
    Solution(int n, vector<int> &blacklist) {
        int bS = blacklist.size();
        wS = n - bS;
        unordered_set<int> bOW;
        for (int b : blacklist) {
            if (b >= wS) {
                bOW.emplace(b);
            }
        }
        int wAv = wS;
        for (int b : blacklist) {
            if (b < wS) {
                while (bOW.count(wAv) != 0) {
                    wAv++;
                }
                b2w[b] = wAv++;
            }
        }
    }

    int pick() {
        wCI %= wS;
        return b2w.count(wCI) != 0 ? b2w[wCI++] : wCI++;
    }
};