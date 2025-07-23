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
        cin>>c;
        int x=read(),y=read();
        if(c=='Q'){
            print(seg.prod(x-1,y));
        }
        else{
            if(seg.get(x-1)<y)seg.set(x-1,y);
        }
    }
}

signed main()
{
    IO(solve);
    return 0;
}