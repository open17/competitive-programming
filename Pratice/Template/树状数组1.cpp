#define USE_STD
// #define REAP_READ
// #define USE_LL
// #define USE_IOS
// #define IN_FILE "data.in"
// #define OUT_FILE "solve.out"
#include <bits/stdc++.h>
#include "template.h"
#include <atcoder/fenwicktree>
using namespace atcoder;


const int N = 5e5 + 5;
const int MOD = 1e9 + 7;


void solve()
{
    int n=read(),m=read();
    atcoder::fenwick_tree<int> fw(n);
    rep(i,0,n){
        fw.add(i,read());
    }
    rep(i,0,m){
        int op=read();
        if(op==1){
            int x=read(),k=read();
            fw.add(x-1,k);
        }
        else{
            int x=read(),y=read();
            print(fw.sum(x-1,y));
        }
    }
}

signed main()
{
    IO(solve);
    return 0;
}