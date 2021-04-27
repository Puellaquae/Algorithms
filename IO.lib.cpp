

/**
 * Shutdown the Sync
void optimize_cpp_stdio() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
}

ios::sync_with_stdio(false);
cout.tie(NULL);
cin.tie(NULL);
*/

/**
 * A fast read write Template From Lougu
 * **/

#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;
namespace IN
{
const int MAX_INPUT = 1000000;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + inbuf->sgetn(buf, MAX_INPUT), p1 == p2) ? EOF : *p1++)
char buf[MAX_INPUT], *p1, *p2;
template <typename T>
inline bool redi(T &x)
{
	static std::streambuf *inbuf = cin.rdbuf();
	x = 0;
	register int f = 0, flag = false;
	register char ch = getc();
	while (!std::isdigit(ch))
	{
		if (ch == '-')
			f = 1;
		ch = getc();
	}
	if (std::isdigit(ch))
		x = x * 10 + ch - '0', ch = getc(), flag = true;
	while (std::isdigit(ch))
	{
		x = x * 10 + ch - 48;
		ch = getc();
	}
	x = f ? -x : x;
	return flag;
}
template <typename T, typename... Args>
inline bool redi(T &a, Args &... args)
{
	return redi(a) && redi(args...);
}
#undef getc
} // namespace IN
namespace OUT
{
template <typename T>
inline void put(T x)
{
	static std::streambuf *outbuf = cout.rdbuf();
	static char stack[21];
	static int top = 0;
	if (x < 0)
	{
		outbuf->sputc('-');
		x = -x;
	}
	if (!x)
	{
		outbuf->sputc('0');
		outbuf->sputc('\n');
		return;
	}
	while (x)
	{
		stack[++top] = x % 10 + '0';
		x /= 10;
	}
	while (top)
	{
		outbuf->sputc(stack[top]);
		--top;
	}
	outbuf->sputc('\n');
}
inline void putc(const char ch)
{
	static std::streambuf *outbuf = cout.rdbuf();
	outbuf->sputc(ch);
}
template <typename T>
inline void put(const char ch, T x)
{
	static std::streambuf *outbuf = cout.rdbuf();
	static char stack[21];
	static int top = 0;
	if (x < 0)
	{
		outbuf->sputc('-');
		x = -x;
	}
	if (!x)
	{
		outbuf->sputc('0');
		outbuf->sputc(ch);
		return;
	}
	while (x)
	{
		stack[++top] = x % 10 + '0';
		x /= 10;
	}
	while (top)
	{
		outbuf->sputc(stack[top]);
		--top;
	}
	outbuf->sputc(ch);
}
template <typename T, typename... Args>
inline void put(T a, Args... args)
{
	put(a);
	put(args...);
}
template <typename T, typename... Args>
inline void put(const char ch, T a, Args... args)
{
	put(ch, a);
	put(ch, args...);
}
} // namespace OUT