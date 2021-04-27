// Milking Time
// Using DP
#include <algorithm>
#include <iostream>
#include <vector>

struct ICow {
    int ST, ED, Eff;
};

bool cmp(ICow a, ICow b) { return a.ST < b.ST; }

using namespace std;

int main() {
    int N, M, R;
    cin >> N >> M >> R;
    vector<ICow> L(M);
    for (int i = 0; i < M; i++) {
        cin >> L[i].ST >> L[i].ED >> L[i].Eff;
        L[i].ED += R;
    }
    sort(L.begin(), L.end(), cmp);
    vector<int> dp(M);
    for (int i = 0; i < M; i++) {
        dp[i] = L[i].Eff;
        //Image this is a List of Interval, each of Interval is a head of its List
        for (int j = 0; j < i; j++) {
            if (L[j].ED <= L[i].ST) {
                //If there is a Interval's Really End_hour less than this Interval's Start_hour
                //Then Assign this Interval Miking after those Interval or Ignore it
                //By Sorted, It needn't to Save the Start_hour and the End_hour of the List
                //Because it's ordered by Start_hour,
                //a previous Interval wouldn't start after any of following Interval
                dp[i] = max(dp[i], dp[j] + L[i].Eff);
                //If the exist list's production is more than the production that Push itself to those List,
                //It won't change
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
}