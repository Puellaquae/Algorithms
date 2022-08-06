#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    long long taskSchedulerII(const vector<int> &tasks, int space) {
        int cnt = 1;
        map<int, long long> last;
        for (auto t : tasks) {
            if (last.count(t) != 0 && (cnt - last[t] - 1) <= space) {
                cnt += space - (cnt - last[t] - 1);
            }
            last[t] = cnt;
            cout << cnt << ": " << t << endl;
            cnt++;
        }
        return cnt - 1;
    }
};

int main() {
    Solution s;
    cout << s.taskSchedulerII({1, 2, 1, 2, 3, 1}, 2) << endl;
    cout << s.taskSchedulerII({5, 8, 8, 5}, 2) << endl;
}