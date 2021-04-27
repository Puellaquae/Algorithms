// Cow Acrobats
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long int64;
const int MAX_N = 5e4 + 5;
const int MAX_S = 1e9 + 5;
int64 N;
struct Cow{
    int64 S,W;
    bool operator<(const Cow& b)const{
        return W + S > b.W + b.S;
    }
};
Cow Cows[MAX_N];
bool C(int64 X) {
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    cin >> N;
    int64 lb = 0, ub = 0;
    for (int64 i = 0; i < N; i++) {
        cin >> Cows[i].W >> Cows[i].S;
        ub+=Cows[i].W;
    }
    sort(Cows,Cows+N);
    int64 risk = -MAX_S;
	for (int i = 0; i < N; i++) {
		ub -= Cows[i].W;
		risk = max(risk, ub - Cows[i].S);
	}
	cout << risk << endl;
    return 0;
    while (lb <= ub) {
        int64 mid = (lb + ub) / 2;
        if (C(mid)) {
            lb = mid + 1;
        } else {
            ub = mid - 1;
        }
    }
}