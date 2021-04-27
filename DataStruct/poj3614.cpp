// Sunscreen
// Using Priority Queue
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Cow {
    int MaxSPF, MinSPF;
    bool operator<(const Cow &b) const { return MinSPF < b.MinSPF; }
};

struct Lotion {
    int SPF, Cover;
    bool operator<(const Lotion &b) const { return SPF < b.SPF; }
};

using namespace std;
int main() {
    int C, T;
    cin >> C >> T;
    vector<Cow> Cows(C);
    vector<Lotion> Lotions(T);
    for (int i = 0; i < C; i++) {
        cin >> Cows[i].MinSPF >> Cows[i].MaxSPF;
    }
    for (int i = 0; i < T; i++) {
        cin >> Lotions[i].SPF >> Lotions[i].Cover;
    }
    sort(Cows.begin(), Cows.end());
    sort(Lotions.begin(), Lotions.end());
    int ans = 0, CowIndex = 0;
    priority_queue<int, vector<int>, greater<int> > CowQueue;
    for (int i = 0; i < T; i++) {
        while (CowIndex < C && Lotions[i].SPF >= Cows[CowIndex].MinSPF) {
            CowQueue.push(Cows[CowIndex++].MaxSPF);
        }
        while (!CowQueue.empty() && Lotions[i].Cover!=0) {
            int MinSPF = CowQueue.top();
            CowQueue.pop();
            if (Lotions[i].SPF > MinSPF)
                continue;
            else {
                ans++;
                Lotions[i].Cover--;
            }
        }
    }
    cout << ans << endl;
}