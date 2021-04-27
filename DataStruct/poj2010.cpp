// Moo University
// Using Greedy, Priority Queue
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Cow {
    int Score, Aid;
    bool operator<(const Cow& b) const {
        if (Score == b.Score) {
            return Aid > b.Aid;
        }
        return Score < b.Score;
    }
};

const int INF = 0x7fffffff;

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int N, C, F;
    cin >> N >> C >> F;
    vector<Cow> Cows;
    for (int i = 0; i < C; i++) {
        int S, A;
        cin >> S >> A;
        Cows.push_back({ S, A });
    }
    sort(Cows.begin(), Cows.end());
    vector<long long> Low(C);
    {
        long long Sum = 0;
        priority_queue<long long> q;
        for (int i = 0; i < N / 2; i++) {
            q.push(Cows[i].Aid);
            Sum += Cows[i].Aid;
            Low[i] = INF;
        }
        for (int i = N / 2; i < C; i++) {
            Low[i] = Sum;
            q.push(Cows[i].Aid);
            Sum += Cows[i].Aid - q.top();
            q.pop();
        }
    }
    vector<long long> High(C);
    {
        long long Sum = 0;
        priority_queue<long long> q;
        for (int i = C - 1; i >= C - N / 2; i--) {
            q.push(Cows[i].Aid);
            Sum += Cows[i].Aid;
            High[i] = INF;
        }
        for (int i = C - N / 2 - 1; i >= 0; i--) {
            High[i] = Sum;
            q.push(Cows[i].Aid);
            Sum += Cows[i].Aid - q.top();
            q.pop();
        }
    }
    int ans = -1;
    for (int i = C - 1; i >= 0; i--) {
        if (High[i] + Low[i] + Cows[i].Aid <= F) {
            ans = Cows[i].Score;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}