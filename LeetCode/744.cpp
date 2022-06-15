#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    char nextGreatestLetter(vector<char>&& letters, char target) {
        auto res = upper_bound(letters.begin(), letters.end(), target);
        if (res == letters.end()) {
            return letters.front();
        } else {
            return *res;
        }
    }
};

int main() {
    Solution solution;
    cout << solution.nextGreatestLetter({'c', 'f', 'j'}, 'a') << endl;
    cout << solution.nextGreatestLetter({'c', 'f', 'j'}, 'c') << endl;
    cout << solution.nextGreatestLetter({'c', 'f', 'j'}, 'd') << endl;
    cout << solution.nextGreatestLetter({'a', 'b'}, 'z') << endl;
}