// Archer

#include <cstdio>
const double ONE = 1.0;
const char FIN[] = "%d%d%d%d";
const char FOUT[] = "%.12f\n";
void Solve() {
    __asm{
        $Start:
        lea eax,[ebp-16]
        push eax
        lea eax,[ebp-12]
        push eax
        lea eax,[ebp-8]
        push eax
        lea eax,[ebp-4]
        push eax
        push offset FIN
        call scanf
        add esp,20
        not eax
        test eax,eax
        je $End
        cvtsi2sd xmm0,dword ptr [ebp-4]
        cvtsi2sd xmm1,dword ptr [ebp-8]
        cvtsi2sd xmm2,dword ptr [ebp-12]
        cvtsi2sd xmm3,dword ptr [ebp-16]
        divsd xmm0,xmm1 ;xmm0 <- Pa
        divsd xmm2,xmm3 ;xmm2 <- Pb
        movsd xmm1,xmm0
        movsd xmm3,qword ptr [ONE]
        subsd xmm3,xmm1 ;xmm3 <- 1.0 - Pa
        movsd xmm1,xmm3 ;xmm1 <- xmm3
        movsd xmm3,qword ptr [ONE]
        subsd xmm3,xmm2 ;xmm3 <- 1.0 - Pb
        movsd xmm2,xmm3 ;xmm2 <- xmm3
        mulsd xmm1,xmm2;
        movsd xmm3,qword ptr [ONE]
        subsd xmm3,xmm1
        divsd xmm0,xmm3
        sub esp,8
        movsd qword ptr [esp],xmm0
        push offset FOUT
        call printf
        add esp,12
        jmp $Start
        $End:
    }
}

int main() { Solve(); }