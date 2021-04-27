#include<cstdio>
#include<cstring>
const int MAXN = 105;
char Plant[MAXN];
int L, PeaNum, MineNum, Step;

void Init() {
    L = strlen(Plant) - 1;
    PeaNum = MineNum = 0;
    for (int i = 0; i <= L; i++) {
        if (Plant[i] == 'P') {
            PeaNum++;
        } else {
            MineNum++;
        }
    }
}

bool Alive(int peaCnt, int peaBefore, int zombieCnt) {
    int nowstep = Step;
    int peaHp = 10, zombieHp = 50;
    while (peaBefore > 0 && zombieCnt > 0) {
        if (nowstep > 0) {
            nowstep--;
            zombieHp -= peaCnt;
        } else {
            peaHp -= zombieCnt;
            zombieHp -= peaCnt;
        }
        if (peaHp <= 0) {
            peaHp = 10;
            peaCnt--;
            peaBefore--;
            nowstep = 1;
        }
        if (zombieHp <= 0) {
            zombieHp = 50;
            zombieCnt--;
        }
    }
    return peaBefore <= 0 && zombieCnt > 0;
}

int Calc(const int peaCnt, const int peaBefore) {
    int l = 1, r = 2 * MAXN;
    while (l <= r) {
        const int mid = (l + r) / 2;
        if (Alive(peaCnt, peaBefore, mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return r + 1;
}

int Solve() {
    Init();
    int zombieNum = 0;
    if (Plant[0] == 'M') {
        zombieNum++;
    }
    if (Plant[L] == 'M') {
        zombieNum++;
        L--;
        Step = 2;
    } else {
        Step = 1;
    }
    while (L >= 0) {
        if (Plant[L] == 'M') {
            if (Step > 1) {
                Step--;
                if (PeaNum >= 50) {
                    zombieNum++;
                }
                continue;
            }
            zombieNum++;
            MineNum--;
            L--;
            Step = 2;
        } else {
            int pnum = 0;
            for (int i = L; i >= 0; i--) {
                if (Plant[i] == 'M') {
                    break;
                }
                pnum++;
            }
            zombieNum += Calc(PeaNum, pnum);
            PeaNum -= pnum;
            L -= pnum + 1;
            Step = 2;
        }
    }
    return zombieNum;
}

int main() {
    int T, Case = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", Plant);  
        printf("Case %d: %d\n", ++Case, Solve());
    }
    return 0;
}