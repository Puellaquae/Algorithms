// Wormholes
// Using Floyd-Warshall

#include <iostream>
#include <vector>
#include <cstring>

const int INF = 0x3f3f3f3f;

using namespace std;

int d[510][510];

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    //cin.tie(0);
    int F;
    cin >> F;
    while (F--) {
        int N, M, W;
        cin >> N >> M >> W;
        memset(d,INF,sizeof(d));
        for (int i = 0; i < N; i++) {
            d[i][i] = 0;
        }
        for (int i = 0; i < M; i++) {
            int S, E, T;
            cin >> S >> E >> T;
            S--;
            E--;
            if (T < d[S][E]) {
                d[S][E] = d[E][S] = T;
            }
        }
        for (int i = 0; i < W; i++) {
            int S, E, T;
            cin >> S >> E >> T;
            d[S - 1][E - 1] = -T;
        }
        int flag = true;
        for (int k = 0; flag && k < N; k++) {
            for (int i = 0; flag && i < N; i++) {
                for (int j = 0; flag && j < N; j++) {
                    if(d[i][j] > d[i][k] + d[k][j]){
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
                if (d[i][i] < 0) {
                    flag = false;
                }
            }
        }
        cout << (!flag ? "YES\n" : "NO\n");
    }
    //cout.flush();
    //system("pause");
}