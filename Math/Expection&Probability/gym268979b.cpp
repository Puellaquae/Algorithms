// Permutation Random Shuffle(Easy Version)

#include <cstdio>
int T;
const char F[] = "%d";
const char ANS[] = "1.0000000\n";
void solve() {
    __asm {
        lea eax,[T]
        push eax
        push offset F
        call scanf
        mov eax,dword ptr [T]
        add esp,8
        $Loop:
        dec eax
        push offset ANS
        mov dword ptr[T],eax
        call printf
        mov eax,dword ptr[T]
        add esp,4
        test eax,eax
        jne $Loop
    }
}
int main() { solve(); }