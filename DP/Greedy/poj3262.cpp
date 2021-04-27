// Protecting the Flowers
// Using Greedy
#include <algorithm>
#include <iostream>
#include <vector>

struct C {
    int T, D;
};

bool cmp(C a, C b) { return (a.D * 1.0 / a.T) > (b.D * 1.0 / b.T); }

using namespace std;
int main() {
    int N;
    cin >> N;
    vector<C> Cows(N);
    for (int i = 0; i < N; i++) {
        cin >> Cows[i].T >> Cows[i].D;
    }
    sort(Cows.begin(), Cows.end(), cmp);
    long long DFlower = 0;
    long long sumD = 0;
    for (int i = 0; i < N; i++)
        sumD += Cows[i].D;
    for (int i = 0; i < N; i++) {
        sumD -= Cows[i].D;
        DFlower += sumD * 2 * Cows[i].T;
    }
    cout << DFlower << endl;
}