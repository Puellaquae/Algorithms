// Sudoku

#include <cstdio>
const char blank = '.';
int neg[] = {0, 0, 0, 3, 3, 3, 6, 6, 6};
int offset[] = {0, 1, 2, 9, 10, 11, 18, 19, 20};
char outbuf[100] = {0};
char inbuf[100];
void show(int grid[][10]) {
    for (int i = 0; i < 81; i++) {
        for (int n = 1; n <= 9; n++) {
            if (grid[i][n] == 1) {
                outbuf[i] = '0' + n;
                break;
            }
        }
    }
    puts(outbuf);
}

bool remove(int grid[][10], int pos, int val);
bool assign(int grid[][10], int pos, int val) {
    grid[pos][0] = 1;
    for (int n = 1; n <= 9; n++) {
        grid[pos][n] = 0;
    }
    grid[pos][val] = 1;
    int row = pos / 9, col = pos % 9;
    for (int i = 0, npos; i < 9; i++) {
        npos = i * 9 + col;
        if (npos != pos && !remove(grid, npos, val)) {
            return false;
        }
    }
    for (int i = 0, npos; i < 9; i++) {
        npos = row * 9 + i;
        if (npos != pos && !remove(grid, npos, val)) {
            return false;
        }
    }
    row = neg[row];
    col = neg[col];
    for (int i = 0, npos; i < 9; i++) {
        npos = row * 9 + col + offset[i];
        if (npos != pos && !remove(grid, npos, val)) {
            return false;
        }
    }
    return true;
}

bool remove(int grid[][10], int pos, int val) {
    if (grid[pos][val] == 1) {
        grid[pos][val] = 0;
        grid[pos][0]--;
        if (grid[pos][0] == 0) {
            return false;
        }
        if (grid[pos][0] == 1) {
            for (int n = 1; n <= 9; n++) {
                if (grid[pos][n] != 0) {
                    return assign(grid, pos, n);
                }
            }
        }
    }
    return true;
}

bool search(int grid[][10]) {
    bool allclear = true;
    int mini = 0, minn = 9;
    for (int i = 0; i < 81; i++) {
        if (grid[i][0] != 1) {
            allclear = false;
            if (grid[i][0] < minn) {
                mini = i;
                minn = grid[i][0];
            }
        }
    }
    if (allclear) {
        show(grid);
        return true;
    }
    int gridcopy[81][10];
    for (int n = 1; n <= 9; n++) {
        if (grid[mini][n] == 1) {
            for (int i = 0; i < 81; i++) {
                for (int j = 0; j < 10; j++) {
                    gridcopy[i][j] = grid[i][j];
                }
            }
            if (assign(gridcopy, mini, n)) {
                if (search(gridcopy)) {
                    return true;
                }
            }
            grid[mini][0]--;
            grid[mini][n] = 0;
        }
    }
    return false;
}

void solve() {
    int grid[81][10];
    for (int i = 0; i < 81; i++) {
        if (inbuf[i] != blank) {
            grid[i][0] = 1;
            for (int n = 1; n <= 9; ++n) {
                grid[i][n] = 0;
            }
            grid[i][inbuf[i] - '0'] = 1;
        } else {
            grid[i][0] = 9;
            for (int j = 1; j <= 9; j++) {
                grid[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < 81; i++) {
        if (inbuf[i] != blank) {
            assign(grid, i, inbuf[i] - '0');
        }
    }
    search(grid);
}

int main() {
    while (scanf("%s", inbuf), inbuf[0] != 'e') {
        solve();
    }
    return 0;
}