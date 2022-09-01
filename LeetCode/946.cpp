#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int pi = 0;
        for (int i = 0; i < pushed.size(); i++) {
            s.push(pushed[i]);
            while (!s.empty() && s.top() == popped[pi]) {
                pi++;
                s.pop();
            }
        }
        while (!s.empty() && s.top() == popped[pi]) {
            pi++;
            s.pop();
        }
        return s.empty();
    }
};