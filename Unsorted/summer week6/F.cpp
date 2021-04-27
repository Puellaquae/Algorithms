#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int t, k = 0;
    while (cin >> t && t) {
        printf("Case #%d:\n", ++k);
        priority_queue<pair<int, int>> A;
        priority_queue<pair<int, int>> B;
        priority_queue<pair<int, int>> C;
        string op, st1, st2;
        int n;
        for (int time = 0; time < t; time++) {
            cin >> op;
            if (op == "push") {
                cin >> st1 >> n;
                if (st1 == "A") {
                    A.push(make_pair(time, n));
                } else {
                    B.push(make_pair(time, n));
                }
            } else if (op == "pop") {
                cin >> st1;
                if (st1 == "A") {
                    if (!A.empty()) {
                        cout << A.top().second << endl;
                        A.pop();
                    } else {
                        cout << C.top().second << endl;
                        C.pop();
                    }
                } else {
                    if (!B.empty()) {
                        cout << B.top().second << endl;
                        B.pop();
                    } else {
                        cout << C.top().second << endl;
                        C.pop();
                    }
                }
            } else {
                cin >> st1 >> st2;
                while (!A.empty()) {
                    C.push(A.top());
                    A.pop();
                }
                while (!B.empty()) {
                    C.push(B.top());
                    B.pop();
                }
            }
        }
    }
}
