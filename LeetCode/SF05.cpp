#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

struct Dsu {
    Dsu(int n) : parent(n, -1) {}
    int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
    void unit(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return;
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
    bool isCompliance(vector<vector<int>> &&distance, int n) {
        int c = distance.size();
        Dsu d(c);
        for (int i = 0; i < c; i++) {
            for (int j = i + 1; j < c; j++) {
                if (distance[i][j] <= 2) {
                    d.unit(i, j);
                }
            }
        }
        unordered_set<int> cnt;
        for (int i = 0; i < c; i++) {
            cnt.insert(d.find(i));
        }
        return cnt.size() <= n;
    }
};

int main() {
    Solution s;
    cout << (s.isCompliance({{0, 3, 3}, {3, 0, 3}, {3, 3, 0}}, 2) ? "T" : "F")
         << endl;
    cout << (s.isCompliance({{0, 1, 3}, {1, 0, 3}, {3, 3, 0}}, 2) ? "T" : "F")
         << endl;
}