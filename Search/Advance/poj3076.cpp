// Sudoku

#include <cstdio>
const char blank = '-';
const char firstEle = 'A' - 1;
const int unitLen = 4;
const int sudokuLen = unitLen * unitLen;
const int gridWidth = sudokuLen + 1;
const int sudokuSize = sudokuLen * sudokuLen;
int neg[sudokuLen] = {0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12};
int offset[sudokuLen] = {0,  1,  2,  3,  16, 17, 18, 19,
                         32, 33, 34, 35, 48, 49, 50, 51};
char outbuf[sudokuSize + 50] = {0};
char inbuf[sudokuSize + 50];
void show(const int *grid) {
    for (int i = 0; i < sudokuSize; i++) {
        for (int n = 1; n <= sudokuLen; n++) {
            if (grid[i * gridWidth + n] == 1) {
                putchar(firstEle + n);
                break;
            }
        }
        if ((i + 1) % sudokuLen == 0)
            puts("");
    }
    puts("");
}

bool remove(int *grid, int pos, int val);
bool assign(int *grid, int pos, int val) {
    grid[pos * gridWidth + 0] = 1;
    for (int n = 1; n <= sudokuLen; n++) {
        grid[pos * gridWidth + n] = 0;
    }
    grid[pos * gridWidth + val] = 1;
    int row = pos / sudokuLen, col = pos % sudokuLen;
    for (int i = 0, npos; i < sudokuLen; i++) {
        npos = i * sudokuLen + col;
        if (npos != pos && !remove(grid, npos, val)) {
            return false;
        }
    }
    for (int i = 0, npos; i < sudokuLen; i++) {
        npos = row * sudokuLen + i;
        if (npos != pos && !remove(grid, npos, val)) {
            return false;
        }
    }
    row = neg[row];
    col = neg[col];
    for (int i = 0, npos; i < sudokuLen; i++) {
        npos = row * sudokuLen + col + offset[i];
        if (npos != pos && !remove(grid, npos, val)) {
            return false;
        }
    }
    return true;
}

bool remove(int *grid, int pos, int val) {
    if (grid[pos * gridWidth + val] == 1) {
        grid[pos * gridWidth + val] = 0;
        grid[pos * gridWidth + 0]--;
        if (grid[pos * gridWidth + 0] < 0) {
            return false;
        }
        if (grid[pos * gridWidth + 0] == 1) {
            for (int n = 1; n <= sudokuLen; n++) {
                if (grid[pos * gridWidth + n] != 0) {
                    return assign(grid, pos, n);
                }
            }
        }
    }
    return true;
}

int checkRow(const int *grid, int row, int val) {
    int p = -1;
    for (int i = 0, pos; i < sudokuLen; i++) {
        pos = row * sudokuLen + i;
        if (grid[pos * gridWidth + 0] == 1 && grid[pos * gridWidth + val] == 1)
            return -1;
        if (grid[pos * gridWidth + 0] == 1)
            continue;
        if (grid[pos * gridWidth + val] == 1) {
            if (p != -1)
                return -1;
            p = i;
        }
    }
    if (p != -1)
        return p;
    return -2;
}

int checkCol(const int *grid, int col, int val) {
    int p = -1;
    for (int i = 0, pos; i < sudokuLen; i++) {
        pos = i * sudokuLen + col;
        if (grid[pos * gridWidth + 0] == 1 && grid[pos * gridWidth + val] == 1)
            return -1;
        if (grid[pos * gridWidth + 0] == 1)
            continue;
        if (grid[pos * gridWidth + val] == 1) {
            if (p != -1)
                return -1;
            p = i;
        }
    }
    if (p != -1)
        return p;
    return -2;
}

int checkUnit(const int *grid, int row, int col, int val) {
    int p = -1;
    for (int i = 0, pos; i < sudokuLen; i++) {
        pos = row * sudokuLen + col + offset[i];
        if (grid[pos * gridWidth + 0] == 1 && grid[pos * gridWidth + val] == 1)
            return -1;
        if (grid[pos * gridWidth + 0] == 1)
            continue;
        if (grid[pos * gridWidth + val] == 1) {
            if (p != -1)
                return -1;
            p = pos;
        }
    }
    if (p != -1)
        return p;
    return -2;
}

bool check(int *grid) {
    for (int i = 0; i < sudokuLen; i++) {
        for (int n = 1, res; n <= sudokuLen; n++) {
            res = checkRow(grid, i, n);
            if (res == -2)
                return false;
            if (res != -1)
                if (!assign(grid, i * sudokuLen + res, n))
                    return false;
        }
    }
    for (int i = 0; i < sudokuLen; i++) {
        for (int n = 1, res; n <= sudokuLen; n++) {
            res = checkCol(grid, i, n);
            if (res == -2)
                return false;
            if (res != -1)
                if (!assign(grid, res * sudokuLen + i, n))
                    return false;
        }
    }
    for (int r = 0, res; r < sudokuLen; r += unitLen) {
        for (int c = 0; c < sudokuLen; c += unitLen) {
            for (int n = 1; n <= sudokuLen; n++) {
                res = checkUnit(grid, r, c, n);
                if (res == -2)
                    return false;
                if (res != -1)
                    if (!assign(grid, res, n))
                        return false;
            }
        }
    }
    return true;
}

bool search(int *grid) {
    if (!check(grid)) {
        return false;
    }
    bool allclear = true;
    int mini = 0, minn = sudokuLen;
    for (int i = 0; i < sudokuSize; i++) {
        if (grid[i * gridWidth + 0] != 1) {
            allclear = false;
            if (grid[i * gridWidth + 0] < minn) {
                mini = i;
                minn = grid[i * gridWidth + 0];
            }
        } else if (grid[i * gridWidth + 0] < 0) {
            return false;
        }
    }
    if (allclear) {
        show(grid);
        return true;
    }
    int *gridcopy = new int[sudokuSize * gridWidth];
    for (int n = 1; n <= sudokuLen; n++) {
        if (grid[mini * gridWidth + n] == 1) {
            for (int i = 0; i < sudokuSize; i++) {
                for (int j = 0; j < gridWidth; j++) {
                    gridcopy[i * gridWidth + j] = grid[i * gridWidth + j];
                }
            }
            if (assign(gridcopy, mini, n)) {
                if (search(gridcopy)) {
                    return true;
                }
            }
            grid[mini * gridWidth + 0]--;
            grid[mini * gridWidth + n] = 0;
        }
    }
    delete[] gridcopy;
    return false;
}

void solve() {
    int *grid = new int[sudokuSize * gridWidth];
    for (int i = 0; i < sudokuSize; i++) {
        if (inbuf[i] != blank) {
            grid[i * gridWidth + 0] = 1;
            for (int n = 1; n <= sudokuLen; ++n) {
                grid[i * gridWidth + n] = 0;
            }
            grid[i * gridWidth + inbuf[i] - firstEle] = 1;
        } else {
            grid[i * gridWidth + 0] = sudokuLen;
            for (int j = 1; j <= sudokuLen; j++) {
                grid[i * gridWidth + j] = 1;
            }
        }
    }
    for (int i = 0; i < sudokuSize; i++) {
        if (inbuf[i] != blank) {
            assign(grid, i, inbuf[i] - firstEle);
        }
    }
    search(grid);
}

int main() {
    int i = 0;
    while (scanf("%s", inbuf) != EOF) {
        for (i = 1; i < sudokuLen; i++) {
            scanf("%s", inbuf + sudokuLen * i);
        }
        solve();
        i = 0;
    }
    return 0;
}