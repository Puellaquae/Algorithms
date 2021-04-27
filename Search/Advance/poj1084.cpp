// Square Destroyer

#include <bitset>
#include <iostream>
using namespace std;

const int MAX_N = 5;
const int MAX_SQUARE_CNT = 55;
const int MAX_EDGE_CNT = 2 * MAX_N * (MAX_N + 1);

int N;
int SquareCnt, EdgeCnt;
bitset<MAX_EDGE_CNT> LackEdges;
bitset<MAX_EDGE_CNT> SquareEdges[MAX_SQUARE_CNT];
bitset<MAX_EDGE_CNT> TakenEdges;

bool Dfs(int sid, int step, int stepLimit) {
    if (sid == SquareCnt) {
        if (step <= stepLimit)
            return true;
        return false;
    }
    if (step > stepLimit)
        return false;
    if ((SquareEdges[sid] & TakenEdges).any())
        return Dfs(sid + 1, step, stepLimit);
    for (int i = 0; i < EdgeCnt; i++) {
        if (!SquareEdges[sid][i])
            continue;
        TakenEdges[i] = true;
        if (Dfs(sid + 1, step + 1, stepLimit))
            return true;
        TakenEdges[i] = false;
    }
    return false;
}

void SquareCheck() {
    for (int i = 0; i < MAX_SQUARE_CNT; i++)
        SquareEdges[i].reset();
    SquareCnt = 0;
    for (int squareSize = 1; squareSize <= N; squareSize++) {
        for (int top = 0; top <= N - squareSize; top++) {
            for (int left = 0; left <= N - squareSize; left++) {
                bool squareValid = true;
                const int topEdgeBegin = top * (2 * N + 1) + left;
                for (int edgeOffset = 0; edgeOffset < squareSize;
                     edgeOffset++) {
                    if (!LackEdges[topEdgeBegin + edgeOffset])
                        SquareEdges[SquareCnt][topEdgeBegin + edgeOffset] =
                            true;
                    else {
                        squareValid = false;
                        break;
                    }
                }
                const int leftEdgeBegin = topEdgeBegin + N;
                for (int edgeOffset = 0; edgeOffset < squareSize && squareValid;
                     edgeOffset++) {
                    if (!LackEdges[leftEdgeBegin + edgeOffset * (2 * N + 1)])
                        SquareEdges[SquareCnt][leftEdgeBegin +
                                               edgeOffset * (2 * N + 1)] = true;
                    else {
                        squareValid = false;
                        break;
                    }
                }
                const int bottomEdgeBegin =
                    topEdgeBegin + squareSize * (2 * N + 1);
                for (int edgeOffset = 0; edgeOffset < squareSize && squareValid;
                     edgeOffset++) {
                    if (!LackEdges[bottomEdgeBegin + edgeOffset])
                        SquareEdges[SquareCnt][bottomEdgeBegin + edgeOffset] =
                            true;
                    else {
                        squareValid = false;
                        break;
                    }
                }
                const int rightEdgeBegin = leftEdgeBegin + squareSize;
                for (int edgeOffset = 0; edgeOffset < squareSize && squareValid;
                     edgeOffset++) {
                    if (!LackEdges[rightEdgeBegin + edgeOffset * (2 * N + 1)])
                        SquareEdges[SquareCnt][rightEdgeBegin +
                                               edgeOffset * (2 * N + 1)] = true;
                    else {
                        squareValid = false;
                        break;
                    }
                }
                if (squareValid)
                    SquareCnt++;
                else
                    SquareEdges[SquareCnt].reset();
            }
        }
    }
}

int main() {
    int t, m;
    cin >> t;
    while (t--) {
        cin >> N;
        EdgeCnt = 2 * N * (N + 1);
        LackEdges.reset();
        cin >> m;
        for (int _ = 0, j; _ < m; _++) {
            cin >> j;
            LackEdges[j - 1] = true;
        }
        SquareCheck();
        TakenEdges.reset();
        for (int stepLimit = 0;; stepLimit++) {
            if (Dfs(0, 0, stepLimit)) {
                cout << stepLimit << endl;
                break;
            }
        }
    }
}