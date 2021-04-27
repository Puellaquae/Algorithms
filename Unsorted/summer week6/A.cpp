#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int t;
    vector<pair<double, int>> scores;
    while (cin >> t && t) {
        scores.clear();
        scores.resize(t);
        for (int i = 0; i < t; i++) {
            cin >> scores[i].first;
            scores[i].second = i + 1;
        }
        sort(scores.begin(), scores.end());
        double ave = 0.0;
        for (int i = 1; i < t - 1; i++) {
            ave += scores[i].first;
        }
        ave /= t - 2.0;
        for (int i = 0; i < t; i++) {
            scores[i].first = abs(scores[i].first - ave);
        }
        cout << min_element(scores.begin(), scores.end())->second << endl;
    }
}