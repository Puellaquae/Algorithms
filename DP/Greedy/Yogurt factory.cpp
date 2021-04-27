#include <vector>
#include <iostream>
#include <algorithm>
struct Yogurt
{
    int C,Y;
};

using namespace std;
int main() {
    int n, s;
    cin >> n >> s;
    vector<Yogurt> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].C >> a[i].Y;
    for (int i = 1; i < n; i++)
        a[i].C = min(a[i].C, a[i - 1].C + s);
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += 1ll * a[i].C * a[i].Y;
    cout << sum << "\n";
    return 0;
}