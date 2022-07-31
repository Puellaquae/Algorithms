#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int maximumGroups(const vector<int>& grades) {
        int n = grades.size();
        int c = 1;
        while (n >= c) {
            n -= c;
            c++;
        }
        return c - 1;
    }
};