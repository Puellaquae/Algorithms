#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k == 1) {
            string minS = s;
            for (int i = 0 ; i < s.size(); i++) {
                minS = min(minS, s.substr(i) + s.substr(0, i));
            }
            return minS;
        } else {
            sort(s.begin(), s.end());
            return s;
        }
    }
};

int main() {
    Solution s;
    cout << s.orderlyQueue("cba", 1) << endl;
    cout << s.orderlyQueue("baaca", 3) << endl;
}