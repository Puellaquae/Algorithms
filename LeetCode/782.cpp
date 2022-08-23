#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int movesToChessboard(const vector<vector<int>> &board) {
        int n = board.size();
        int ltime = 0;
        int rtime = 0;
        for (int i = 0; i < n; i++) {
            {
                int dif0 = 0, dif1 = 0;
                int curd = 1;
                int one = 0, zero = 0;
                for (int j = 0; j < n; j++) {
                    int v = board[i][j];
                    one += v == 1;
                    zero += v == 0;
                    dif0 += v == curd;
                    dif1 += v != curd;
                    curd = 1 - curd;
                }
                if (abs(one - zero) > 1) {
                    return -1;
                }
                int nltime;
                if (n % 2 == 1) {
                    nltime = (one > zero ? dif1 : dif0) / 2;
                    if (n > 3 && (one > zero ? dif1 : dif0) % 2 == 1) {
                        nltime += board[i][n / 2] == (zero > one);
                    }
                } else {
                    nltime = min(dif0, dif1) / 2;
                }
                if (ltime != nltime && i != 0) {
                    return -1;
                }
                ltime = nltime;
            }
            {
                int dif0 = 0, dif1 = 0;
                int curd = 1;
                int one = 0, zero = 0;
                for (int j = 0; j < n; j++) {
                    int v = board[j][i];
                    one += v == 1;
                    zero += v == 0;
                    dif0 += v == curd;
                    dif1 += v != curd;
                    curd = 1 - curd;
                }
                if (abs(one - zero) > 1) {
                    return -1;
                }
                int nrtime;
                if (n % 2 == 1) {
                    nrtime = (one > zero ? dif1 : dif0) / 2;
                    if (n > 3 && (one > zero ? dif1 : dif0) % 2 == 1) {
                        nrtime += board[n / 2][i] == (zero > one);
                    }
                } else {
                    nrtime = min(dif0, dif1) / 2;
                }
                if (nrtime != rtime && i != 0) {
                    return -1;
                }
                rtime = nrtime;
            }
        }
        return ltime + rtime;
    }
};

int main() {
    Solution s;
    cout << s.movesToChessboard(
                {{0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}})
         << endl;
    cout << s.movesToChessboard({{1, 1, 0}, {0, 0, 1}, {0, 0, 1}}) << endl;
    cout << s.movesToChessboard({{1, 0}, {0, 1}}) << endl;
    cout << s.movesToChessboard({{1, 0, 0}, {0, 1, 1}, {1, 0, 0}}) << endl;
    cout << s.movesToChessboard({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}) << endl;
    cout << s.movesToChessboard(
                {{0, 0, 1, 1}, {1, 1, 0, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}})
         << endl;
    cout << s.movesToChessboard({{1, 0, 0, 1, 1},
                                 {0, 1, 1, 0, 0},
                                 {1, 0, 0, 1, 1},
                                 {0, 1, 1, 0, 0},
                                 {0, 1, 1, 0, 0}})
         << endl;
}