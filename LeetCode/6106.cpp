#include <iostream>
#include <unordered_map>
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
    long long countPairs(int n, const vector<vector<int>> &edges) {
        Dsu dsu(n);
        for (auto &edge : edges) {
            dsu.unit(edge[0], edge[1]);
        }
        unordered_map<int, int> gM;
        for (int i = 0; i < n; i++) {
            gM[dsu.find(i)]++;
        }
        long long cnt = 0;
        for (auto &p : gM) {
            cnt += (long long) p.second * (n - p.second);
        }
        return cnt / 2;
    }

    long long countPairsOld(int n, const vector<vector<int>> &edges) {
        Dsu dsu(n);
        for (auto &edge : edges) {
            dsu.unit(edge[0], edge[1]);
        }
        unordered_map<int, int> gM;
        for (int i = 0; i < n; i++) {
            gM[dsu.find(i)]++;
        }
        vector<int> gV;
        for (auto &p : gM) {
            gV.push_back(p.second);
        }
        int gC = gV.size();
        long long cnt = 0;
        for (int i = 0; i < gC; i++) {
            for (int j = i + 1; j < gC; j++) {
                cnt += gV[i] * gV[j];
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    cout << s.countPairs(3, {{0, 1}, {0, 2}, {1, 2}}) << endl;
    cout << s.countPairs(7, {{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}}) << endl;
    cout << s.countPairs(10000, {{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}})
         << endl;
}