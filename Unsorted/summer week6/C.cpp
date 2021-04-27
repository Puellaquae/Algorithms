#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

bool OperatorQ(const char str) {
    return str == '+' || str == '-' || str == '*' || str == '/' || str == '=';
}

int minbase(const char *str) {
    int base = 0;
    while (*str) {
        if (OperatorQ(*str)) { } else if ('0' <= *str && *str <= '9') {
            base = max(base, *str - '0' + 1);
        } else {
            base = max(base, *str - 'A' + 11);
        }
        str++;
    }
    return base;
}

ll str2i(char *&str, const int base) {
    ll ans = 0;
    int digit;
    while (*str && !OperatorQ(*str)) {
        if ('0' <= *str && *str <= '9') {
            digit = *str - '0';
        } else {
            digit = *str - 'A' + 10;
        }
        ans = ans * base + digit;
        str++;
    }
    return ans;
}

bool Check(const ll a, const char op, const ll b, const ll c) {
    switch (op) {
        case '+':
            return a + b == c;
        case '-':
            return a - b == c;
        case '*':
            return a * b == c;
        case '/':
            return c * b == a;
        default:
            return false;
    }
}

char Line[32];

int main() {
    while (~scanf("%s", Line)) {
        int base = minbase(Line);
        for (ll a, b, c; base <= 16; base++) {
            char *str = Line;
            a = str2i(str, base);
            const char op = *str++;
            b = str2i(str, base);
            c = str2i(++str, base);
            if (Check(a, op, b, c) && base >= 2) {
                cout << base << "\n";
                break;
            }
        }
        if (base > 16) {
            cout << "-1\n";
        }
    }
}
