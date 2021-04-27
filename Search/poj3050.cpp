//Hopscotch
#include <iostream>
#include <map>
#include <set>
#include <string>

const int Stop = -1;
using namespace std;

#define NextMove                      \
    do {                              \
        if (x > 0)                    \
            Move(M, x - 1, y, Built); \
        if (x < 4)                    \
            Move(M, x + 1, y, Built); \
        if (y > 0)                    \
            Move(M, x, y - 1, Built); \
        if (y < 4)                    \
            Move(M, x, y + 1, Built); \
    } while (0)

set<string> Rus;

void Move(int M[5][5], int x, int y, string Built)
{
    Built += M[x][y] + '0';
    if (Built.size() == 6) {
        Rus.insert(Built);
    } else {
        NextMove;
    }
}

int main()
{
    int M[5][5];
    map<int, int[4]> MoveMap;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> M[i][j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Move(M, i, j, "");
        }
    }
    cout << Rus.size() << endl;
}