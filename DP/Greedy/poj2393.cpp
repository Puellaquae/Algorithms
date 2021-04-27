//Yogurt factory
//Using Greedy
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Yogurt {
    int C;
    int Y;
};

bool cmp(Yogurt a, Yogurt b) {}

int main() {
    int N;
    int StoreYFeePWeek;
    cin >> N >> StoreYFeePWeek;
    vector<Yogurt> Fucky(N);
    for (int i = 0; i < N; i++) {
        cin >> Fucky[i].C >> Fucky[i].Y;
    }
    if (N == 1) {
        cout << Fucky[0].C * Fucky[1].Y << endl;
    }
    long long TCost = 0;
}