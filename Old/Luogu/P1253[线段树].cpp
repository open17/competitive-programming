/*


考虑两个标记的先后顺序问题

注意单次是1e9但是可以累加会溢出

因为没有考虑溢出用-0x3f3f3f导致错误debug了半天,引以为戒

另外最后一个点卡常,要全快读


*/



#include <bits/stdc++.h>

/*
 *
 *   宏定义模板常量:
 *
 *          使用STD
 *          重复数据读入
 *          int强制转ll
 *          启用debug输出
 *          关闭输入同步流
 *          使用文件输入流
 *          使用文件输出流
 *
 */

#define USE_STD
#define USE_LL
// #define REAP_READ
// #define USE_DEBUG
// #define USE_IOS
// #define IN_FILE "data.in"
// #define OUT_FILE "solve.out"

#ifdef USE_STD
using namespace std;
#endif

#ifdef USE_LL
#define int long long
#endif

// 辅助宏
#define rep(i, l, r) for (int i = (l); i < (r); i++)
#define _rep(i, l, r) for (int i = (l); i < (r); i++)
#define all(x) (x).begin(), x.end()
#define inf 0x3f3f3f3f
#define endl '\n' // 避免刷新缓冲区

// 类型别名
using i64 = long long;
using u64 = unsigned long long;
using pii = std::pair<int, int>;

// 常规输出
template <typename T>
void print(const T &t) { std::cout << t << endl; }
template <typename T, typename... Args>
void print(const T &t, const Args... args)
{
    std::cout << t << ' ';
    print(args...);
}

// USE_DEBUG 模式下的输出
template <typename T>
void debug(const T &t)
{
#ifdef USE_DEBUG
    std::cout << t << "\n";
#endif
}
template <typename T, typename... Args>
void debug(const T &t, const Args... args)
{
#ifdef USE_DEBUG
    std::cout << t << ' ';
    debug(args...);
#endif
}

// 快读快写
int read();
void write(int);

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int val[N];
int node[N << 2], todo[N << 2], todo2[N << 2][2];

void _do2(int p, int v)
{
    node[p] = v;
    todo2[p][0] = v;
    todo2[p][1] = 1;
    todo[p] = 0;
}

void _do(int p, int size, int v)
{
    node[p] += v;
    if (todo2[p][1])
    {
        todo2[p][0] += v;
    }
    else
    {
        todo[p] += v;
    }
}

void _down(int p, int l, int r)
{
    if (l >= r)
        return;
    int size = r - l + 1;
    if (todo2[p][1])
    {
        _do2(p * 2, todo2[p][0]);
        _do2(p * 2 + 1, todo2[p][0]);
        todo2[p][1] = 0;
    }
    else
    {
        _do(p * 2, size - size / 2, todo[p]);
        _do(p * 2 + 1, size / 2, todo[p]);
        todo[p] = 0;
    }
}

void _up(int p)
{
    node[p] = max(node[p * 2], node[p * 2 + 1]);
}

void build(int p, int l, int r)
{
    if (l == r)
    {
        node[p] = val[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    _up(p);
}

void update(int p, int l, int r, int L, int R, int v)
{
    if (L <= l and r <= R)
    {
        _do(p, r - l + 1, v);
        return;
    }
    int mid = (l + r) >> 1;
    _down(p, l, r);
    if (mid >= L)
        update(p * 2, l, mid, L, R, v);
    if (mid < R)
        update(p * 2 + 1, mid + 1, r, L, R, v);
    _up(p);
}

void update2(int p, int l, int r, int L, int R, int v)
{
    if (L <= l and r <= R)
    {
        _do2(p, v);
        return;
    }
    int mid = (l + r) >> 1;
    _down(p, l, r);
    if (mid >= L)
        update2(p * 2, l, mid, L, R, v);
    if (mid < R)
        update2(p * 2 + 1, mid + 1, r, L, R, v);
    _up(p);
}

i64 query(int p, int l, int r, int L, int R)
{
    if (L <= l and r <= R)
    {
        return node[p];
    }
    _down(p, l, r);
    i64 ans = LONG_LONG_MIN;
    int mid = (l + r) >> 1;
    if (mid >= L)
        ans = max(ans, query(p * 2, l, mid, L, R));
    if (mid < R)
        ans = max(ans, query(p * 2 + 1, mid + 1, r, L, R));
    return ans;
}

void solve()
{
    int n = read(), q = read();
    int l, r, x;
    rep(i, 0, n) val[i + 1] = read();
    build(1, 1, n);
    rep(i, 0, q)
    {
        int op = read();
        l = read();
        r = read();
        if (op == 2)
        {
            x = read();
            // cin >> l >> r >> x;
            update(1, 1, n, l, r, x);
        }
        else if (op == 1)
        {
            x = read();
            // cin >> l >> r >> x;
            update2(1, 1, n, l, r, x);
        }
        else
        {
            // cin >> l >> r;
            print(query(1, 1, n, l, r));
        }
    }
}

signed main()
{
    int T = 1;
#ifdef IN_FILE
    freopen(IN_FILE, "r", stdin);
#endif

#ifdef OUT_FILE
    freopen(OUT_FILE, "w", stdout);
#endif

#ifdef REAP_READ
    std::cin >> T;
#endif

#ifdef USE_IOS
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
#endif

    while (T--)
    {
        solve();
    }
    return 0;
}

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
