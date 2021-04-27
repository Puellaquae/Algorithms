#include <iostream>
#include <string>
using namespace std;

string In;
string Out;

string GetNumber(int &idx) {
    const int oidx = idx;
    while (In[idx++] != ')') {}
    return In.substr(oidx, idx - oidx - 1);
}

void GetBombTerm(int &idx) {
    if (In[idx] == '(') {
        const string num = GetNumber(++idx);
        idx += 2;
        const int times = In[idx++] - '0';
        idx++;
        for (int i = 0; i < times; i++) {
            Out += num;
        }
    } else {
        while (isdigit(In[idx])) {
            Out.push_back(In[idx++]);
        }
    }
}


void BombNumber() {
    Out.clear();
    int idx = 0;
    while (idx < In.size()) {
        GetBombTerm(idx);
    }
}

template<int Mod>
long long StrMod(const string& str) {
    long long sum = 0;
    for (int i = 0; i < str.size(); i++)
    {
        sum = (sum * 10ll + (str[i] - '0')) % Mod;
    }
    return sum;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> In;
        BombNumber();
        cout << StrMod<1000000007>(Out) << endl;
    }
    return 0;
}