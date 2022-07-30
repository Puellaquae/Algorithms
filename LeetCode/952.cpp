#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Dsu {
    Dsu(int n): parent(n, -1) {}
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    void unit(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (parent[u] < parent[v])
            std::swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }
private:
    std::vector<int> parent;
};

class Solution {
public:
    int largestComponentSize(const vector<int> &nums) {
        int range = *max_element(nums.begin(), nums.end());
        Dsu dsu(range + 1);
        for (auto n: nums) {
            for (int i = 2; i <= sqrt(n); i++) {
                if (n % i == 0) {
                    dsu.unit(n, i);
                    dsu.unit(n , n / i);
                }
            }
        }
        vector<int> count(range + 1, 0);
        int maxC = 0;
        for (auto n : nums) {
            maxC = max(maxC, ++count[dsu.find(n)]);
        }
        return maxC;
    }
};

int main() {
    Solution s;
    cout << s.largestComponentSize({4, 6, 15, 35}) << endl;
    cout << s.largestComponentSize({20, 50, 9, 63, 17}) << endl;
    cout << s.largestComponentSize({2, 3, 6, 7, 4, 12, 21, 39}) << endl;
}