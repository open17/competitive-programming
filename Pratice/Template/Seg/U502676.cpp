// #define REAP_READ
// #define USE_LL
// #define USE_IOS
// #define IN_FILE "data.in"
// #define OUT_FILE "solve.out"
#define USE_STD
#include <bits/stdc++.h>
#include "template.h"
#include <atcoder/segtree>
using namespace atcoder;


const int N = 5e5 + 5;
const int MOD = 1e9 + 7;

int op(int a, int b) {
    return max(a, b);
}

int e() {
    return (int)(-1);
}

void solve()
{
    int n=read(),m=read();
    vector<int> v(n);
    rep(i,0,n)v[i]=read();
    segtree<int, op, e> seg(v);
    char c;
    rep(i,0,m){
        int x=read(),y=read(),k=read();
        auto f = [&](int mx) { return mx <= k; };
        int r=seg.max_right(x-1,f);
        if(r<y)print(r+1);
        else print(-1);
    }
}

signed main()
{
    IO(solve);
    return 0;
}