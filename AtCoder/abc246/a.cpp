#include <iostream>
using namespace std;

using vec = pair<int, int>;

int dot(const vec &a, const vec &b) {
    return a.first * b.first + a.second * b.second;
}

vec add(const vec &a, const vec &b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

vec sub(const vec &a, const vec &b) {
    return make_pair(a.first - b.first, a.second - b.second);
}

int main() {
    vec a, b, c, d;
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    cin >> c.first >> c.second;
    if (dot(sub(b, a), sub(c, a)) == 0) {
        d = add(a, add(sub(b, a), sub(c, a)));
    } else if (dot(sub(a, b), sub(c, b)) == 0) {
        d = add(b, add(sub(a, b), sub(c, b)));
    } else {
        d = add(c, add(sub(a, c), sub(b, c)));
    }
    cout << d.first << " " << d.second << endl;
    return 0;
}