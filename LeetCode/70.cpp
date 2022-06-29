#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
    unordered_map<int, int> mem;
public:
    int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        if (mem.count(n) != 0) {
            return mem[n];
        }
        int res = climbStairs(n - 1) + climbStairs(n - 2);
        mem[n] = res;
        return res;
    }
};