// 统计难题

#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;
map<string, int> v;
char ss[20];
int main() {
    while (gets(ss)) {
        if (ss[0] == '\0')
            break;
        int l = strlen(ss);
        string s;
        for (int i = 0; i < l; i++) {
            s += ss[i];
            v[s]++;
        }
    }
    string s;
    while (cin >> s)
        cout << v[s] << endl;
}
