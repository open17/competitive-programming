/**
 * @title: Photoshoot for Gorillas
 * @desc: ...
 * @tag: 贡献/贪心/思维
 * @url: 
 */


#include <bits/stdc++.h>

/*
 *
 *   宏定义模板常量:
 *
 *          使用STD
 *          重复数据读入
 *          int强制转ll
 *          重载工具函数
 *          启用debug输出
 *          关闭输入同步流
 *          使用文件输入流
 *          使用文件输出流
 *
 */

#define USE_STD
#define USE_LL
#define REAP_READ
#define USE_TOOL
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
#define _rep(i, l, r) for (int i = (l); i >= (r); i--)
#define all(x) (x).begin(), x.end()
#define endl '\n'  // 避免刷新缓冲区
#define inf32 0x3f3f3f3f
#define max32 INT_MAX


// 类型别名
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using pii = std::pair<int, int>;

// 常规输出
template <typename T> void print(const T &t) { std::cout << t << endl; }
template <typename T, typename... Args> void print(const T &t, const Args... args)
{
    std::cout << t << ' ';
    print(args...);
}

// USE_DEBUG 模式下的输出
template <typename T> void debug(const T &t) { 
    #ifdef USE_DEBUG
    std::cout << t << "\n\n"; 
    #endif
}
template <typename T, typename... Args> void debug(const T &t, const Args... args)
{
    #ifdef USE_DEBUG
    std::cout << t << ' ';
    debug(args...);
    #endif
}

#ifdef USE_TOOL
i64 ceilDiv(i64 n, i64 m) {
    if (n >= 0) {
        return (n + m - 1) / m;
    } else {
        return n / m;
    }
}
 
i64 floorDiv(i64 n, i64 m) {
    if (n >= 0) {
        return n / m;
    } else {
        return (n - m + 1) / m;
    }
}

template<class T>
void chmax(T &a, T b) {
    if (a < b) {
        a = b;
    }
}

i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}

#endif

// 快读快写
int read();
void write(int);

const int N = 5e5 + 5;
const int MOD = 1e9 + 7;

void solve()
{
    int n=read(),m=read(),k=read(),w=read();
    vector<int> a(w);
    rep(i,0,w){
        a[i]=read();
    }
    sort(a.begin(),a.end(),greater<int>());
    // 贡献  (i,j) 
    vector<int> val;
    rep(i,0,n){
        rep(j,0,m){
            int l,r,u,d;
            r=min(j,m-k);
            l=max(0LL,j-k+1);
            u=max(0LL,i-k+1);
            d=min(i,n-k);
            val.push_back((r-l+1)*(d-u+1));
        }
    }
    sort(val.begin(),val.end(),greater<int>());
    int ans=0;
    rep(i,0,w){
        // print(val[i],a[i]);
        ans+=val[i]*a[i];
    }
    print(ans);
}

signed main()
{
    int T = 1;
    debug("hello world");
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