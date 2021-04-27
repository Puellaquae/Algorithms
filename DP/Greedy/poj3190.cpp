// Stall Reservations
// Using Greedy, Priority Queue
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cow {
    int Left, Right;
    int OriginIndex;
};

bool OrderByLeft(Cow a, Cow b) { return a.Left < b.Left; }

struct Stall {
    int Right, Index;
    bool operator<(const Stall &a) const {
        return Right > a.Right;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<Cow> Cows(N);
    for (int i = 0; i < N; i++) {
        cin >> Cows[i].Left >> Cows[i].Right;
        Cows[i].OriginIndex = i;
    }
    sort(Cows.begin(), Cows.end(), OrderByLeft);
    vector<int> GetOriginIndex(N);
    for (int i = 0; i < N; i++) {
        GetOriginIndex[i] = Cows[i].OriginIndex;
    }
    priority_queue<Stall> Stalls;
    vector<int> Throw2Which(N);
    for (int i = 0; i < N; i++) {
        int OriginIndex = GetOriginIndex[i];
        Throw2Which[OriginIndex] = Stalls.size();
        if (!Stalls.empty() && Stalls.top().Right < Cows[i].Left) {
            Throw2Which[OriginIndex] = Stalls.top().Index;
            Stalls.pop();
        }
        Stalls.push({Cows[i].Right, Throw2Which[OriginIndex]});
    }
    cout << Stalls.size() << '\n';
    for (int i = 0; i < N; i++) {
        cout << Throw2Which[i] + 1 << '\n';
    }
    return 0;
}
