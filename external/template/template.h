#ifndef TEMPLATE_H
#define TEMPLATE_H

#ifdef USE_LL
#define int long long
#endif

#ifdef USE_STD
using namespace std;
#endif

// 辅助宏
#define rep(i, l, r) for (int i = (l); i < (r); i++)
#define _rep(i, l, r) for (int i = (l); i >= (r); i--)
#define all(x) (x).begin(), x.end()
#define endl '\n' // 避免刷新缓冲区
#define inf32 0x3f3f3f3f
#define inf64 1LL << 60
#define max32 INT_MAX
#define debug(x) cout << #x << " = " << x << "\n";
#define vdebug(a) cout << #a << " = "; for (auto x : a) cout << x << " "; cout << "\n";

// 类型别名
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using pii = std::pair<int, int>;

// print
template <typename T>
void print(const T &t) { std::cout << t << endl; }
template <typename T, typename... Args>
void print(const T &t, const Args... args)
{
    std::cout << t << ' ';
    print(args...);
}

i64 ceilDiv(i64 n, i64 m)
{
    if (n >= 0)
    {
        return (n + m - 1) / m;
    }
    else
    {
        return n / m;
    }
}

i64 floorDiv(i64 n, i64 m)
{
    if (n >= 0)
    {
        return n / m;
    }
    else
    {
        return (n - m + 1) / m;
    }
}

template <class T>
void chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
    }
}

template <class T>
void chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
    }
}

template <class T>
T gcd(T a, T b)
{
    return b ? gcd(b, a % b) : a;
}

// 快读快写实现
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void write(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void IO(void (*solve_func)())
{
    int TEM_T = 1;
#ifdef IN_FILE
    freopen(IN_FILE, "r", stdin);
#endif

#ifdef OUT_FILE
    freopen(OUT_FILE, "w", stdout);
#endif

#ifdef REAP_READ
    std::cin >> TEM_T;
#endif

#ifdef USE_IOS
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
#endif
    while (TEM_T--)
    {
        solve_func();
    }
}

#endif // TEMPLATE_H