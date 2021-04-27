// Stripies
// Using Greedy
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
bool cmp(int a, int b) { return a > b; }

int main() {
    int N;
    cin >> N;
    vector<int> Pki(N);
    for (int i = 0; i < N; i++) {
        cin >> Pki[i];
    }
    if(N==1){
        printf("%.3f",Pki[0]*1.0f);
        return 0;
    }
    sort(Pki.begin(), Pki.end(), cmp);
    double Ans = 0;
    Ans = 2.0 * sqrt(Pki[0] * Pki[1] * 1.0);
    for (int i = 2; i < N; i++) {
        Ans = 2.0 * sqrt(Pki[i] * Ans * 1.0);
    }
    printf("%.3f\n",Ans);
    return 0;
}