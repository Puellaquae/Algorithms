// Backward Digit Sums
#include<iostream>
#include<algorithm>
using namespace std;
const int YH[10][10] = {
    {1, 0,  0,  0,   0,   0,  0,  0,  0,  0},
    {1, 1,  0,  0,   0,   0,  0,  0,  0,  0},
    {1, 2,  1,  0,   0,   0,  0,  0,  0,  0},
    {1, 3,  3,  1,   0,   0,  0,  0,  0,  0},
    {1, 4,  6,  4,   1,   0,  0,  0,  0,  0},
    {1, 5, 10, 10,   5,   1,  0,  0,  0,  0},
    {1, 6, 15, 20,  15,   6,  1,  0,  0,  0},
    {1, 7, 21, 35,  35,  21,  7,  1,  0,  0},
    {1, 8, 28, 56,  70,  56, 28,  8,  1,  0},
    {1, 9, 36, 84, 126, 126, 84, 36,  9,  1},
    };

int main(){
    int n,sum;
    cin>>n>>sum;
    int Num[10]={1,2,3,4,5,6,7,8,9,10};
    do{
        int Tsum=0;
        for(int i=0;i<n;i++){
            Tsum+=YH[n-1][i]*Num[i];
        }
        if(Tsum==sum){
            for(int i=0;i<n;i++){
                cout<<Num[i]<<" ";
            }
            cout<<endl;
            break;
        }
    }while(next_permutation(Num,Num+n));
    return 0;
}