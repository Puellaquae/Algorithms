// 概率论

#include <cstdio>
using namespace std;
int main(void)
{
	int n;
	scanf("%d", &n);
	printf("%.9lf", 1.0 * (n + 1) * n / (1.0 * n * 4 - 2));
}