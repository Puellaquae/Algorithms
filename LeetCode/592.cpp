#include <deque>
#include <iostream>
#include <string>

using namespace std;

enum class TokType { Val, Add, Sub };

struct Tok {
    TokType type;
    int fm, fz;
};

template <class T> T gcd(T a, T b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

class Solution {
public:
    string fractionAddition(string expression) {
        deque<Tok> toks;
        int fm = 0;
        int fz = 0;
        bool isFz = true;
        for (auto ch : expression) {
            if (ch == '-') {
                toks.push_back(Tok{TokType::Val, fm, fz});
                fm = fz = 0;
                isFz = true;
                toks.push_back(Tok{TokType::Sub});
            } else if (ch == '+') {
                toks.push_back(Tok{TokType::Val, fm, fz});
                fm = fz = 0;
                isFz = true;
                toks.push_back(Tok{TokType::Add});
            } else if (ch == '/') {
                isFz = false;
            } else if ('0' <= ch && ch <= '9') {
                if (isFz) {
                    fz = fz * 10 + ch - '0';
                } else {
                    fm = fm * 10 + ch - '0';
                }
            }
        }
        toks.push_back(Tok{TokType::Val, fm, fz});
        int fmAns = 0;
        int fzAns = 0;
        TokType lastOp = TokType::Val;
        for (auto &tok : toks) {
            if (tok.type == TokType::Val) {
                if (lastOp == TokType::Val) {
                    fmAns = tok.fm == 0 ? 1 : tok.fm;
                    fzAns = tok.fz;
                } else {
                    if (fmAns != tok.fm) {
                        tok.fz *= fmAns;
                        fzAns *= tok.fm;
                        tok.fm = fmAns = tok.fm * fmAns;
                    }
                    if (lastOp == TokType::Add) {
                        fzAns += tok.fz;
                    } else {
                        fzAns -= tok.fz;
                    }
                }
            } else {
                lastOp = tok.type;
            }
        }
        int g = gcd(fmAns, fzAns);
        fmAns /= g;
        fzAns /= g;
        string ans = "";
        if (fzAns * fmAns < 0) {
            ans += "-";
        }
        ans += to_string(abs(fzAns)) + "/" + to_string(abs(fmAns));
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.fractionAddition("-1/2+1/2") << endl;
    cout << s.fractionAddition("-1/2+1/2+1/3") << endl;
    cout << s.fractionAddition("1/3-1/2") << endl;
}