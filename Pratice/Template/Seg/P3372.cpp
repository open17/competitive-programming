// #define REAP_READ
// #define USE_LL
// #define USE_IOS
// #define IN_FILE "data.in"
// #define OUT_FILE "solve.out"
#define USE_STD
#include <bits/stdc++.h>
#include "template.h"
#include <atcoder/lazysegtree>
using namespace atcoder;


const int N = 5e5 + 5;
const int MOD = 1e9 + 7;

struct S {
    i64 sum;
    int len;
};


S op(S a, S b) {
    return { a.sum + b.sum, a.len + b.len };
}

S e() {
    return { 0ll, 0ll };
}

struct F {
    i64 add;
};

F composition(F a, F b) {
    return { a.add + b.add };
}

F id() {
    return { 0 };
}

S mapping(F f, S x) {
    return { x.sum + f.add * x.len, x.len };
}


void solve()
{
    int n=read(),m=read();
    vector<S> v(n,{0, 1});
    rep(i,0,n)v[i].sum=read();
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
    rep(i,0,m){
        int op=read();
        int x=read(),y=read();
        if(op==1){
            i64 k=read();
            seg.apply(x-1,y,F{k});
        }
        else{
            print(seg.prod(x-1,y).sum);
        }
    }
}

signed main()
{
    IO(solve);
    return 0;
}