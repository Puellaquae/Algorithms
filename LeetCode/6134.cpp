#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int closestMeetingNode(const vector<int> &edges, int node1, int node2) {
        int n = edges.size();
        vector<int> n1dis(n, 0x7f7f7f7f);
        vector<int> n2dis(n, 0x7f7f7f7f);
        int c1 = node1;
        int d1 = 0;
        for (;;) {
            n1dis[c1] = d1++;
            c1 = edges[c1];
            if (c1 == -1 || n1dis[c1] != 0x7f7f7f7f) {
                break;
            }
        }
        int c2 = node2;
        int d2 = 0;
        for (;;) {
            n2dis[c2] = d2++;
            c2 = edges[c2];
            if (c2 == -1 || n2dis[c2] != 0x7f7f7f7f) {
                break;
            }
        }
        int minD = 0x7f7f7f7f;
        int minI = -1;
        for (int i = 0; i < n; i++) {
            if (max(n1dis[i], n2dis[i]) < minD) {
                minI = i;
                minD = max(n1dis[i], n2dis[i]);
            }
        }
        return minI;
    }
};

int main() {
    Solution s;
    cout << s.closestMeetingNode({2, 2, 3, -1}, 0, 1) << endl;
    cout << s.closestMeetingNode({1, 2, -1}, 0, 2) << endl;
    cout << s.closestMeetingNode({4, 3, 0, 5, 3, -1}, 4, 0) << endl;
}