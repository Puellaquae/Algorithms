#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
using namespace std;

void CalcCanvasSize(const int a,
                    const int b,
                    const int c,
                    int &canvasWidth,
                    int &canvasHeight) {
    canvasWidth = a * 2 + 1 + b * 2;
    canvasHeight = c * 2 + 1 + b * 2;
}

// i in [l, r]
bool OnRange(const int i, const int l, const int r) {
    return l <= i && i <= r;
}

// i in [top, top + len]
bool OnLine(const int i, const int top, const int len) {
    return top <= i && i <= top + len;
}

char Sample(const int i,
            const int j,
            const int height,
            const int width,
            const int a,
            const int b,
            const int c) {

    if (i % 2 == 0 && j % 2 == 0) {
        if (OnRange(i + j, b * 2, height + width - b * 2 - 2)) {
            return '+';
        }
    } else if (i % 2 == 1 && j % 2 == 0) {
        if (j <= a * 2 && i >= b * 2 ||
            a * 2 < j && OnLine(i, width - j, c * 2 - 1)) {
            return '|';
        }
    } else if (i % 2 == 0 && j % 2 == 1) {
        if (i >= b * 2 && j <= a * 2 ||
            b * 2 > i && OnLine(j, width - i - a * 2, a * 2 - 1)) {
            return '-';
        }
    } else {
        if (i < min(b, c) * 2 && j >= width - i - a * 2 - 2 ||
            c * 2 <= i && i < b * 2 && OnLine(j, width - i - a * 2 - 2, a * 2 + c * 2 + 2) ||
            i >= b * 2 && OnLine(j, a * 2, height - i)) {
            return '/';
        }
    }
    return '.';
}

void Draw(const int a, const int b, const int c) {
    int canvasWidth, canvasHeight;
    CalcCanvasSize(a, b, c, canvasWidth, canvasHeight);
    for (int i = 0; i < canvasHeight; i++) {
        for (int j = 0; j < canvasWidth; j++) {
            cout << Sample(i, j, canvasHeight, canvasWidth, a, b, c);
        }
        cout << endl;
    }
}

int main() {
    int t, a, b, c;
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        Draw(a, b, c);
    }
}
