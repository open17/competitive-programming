// #define REAP_READ
// #define USE_LL
// #define USE_IOS
// #define IN_FILE "data.in"
// #define OUT_FILE "solve.out"
#define USE_STD
#include <bits/stdc++.h>
#include "template.h"
#include <atcoder/fenwicktree>
using namespace atcoder;


const int N = 5e5 + 5;
const int MOD = 1e9 + 7;


void solve()
{
    int n=read(),m=read();
    vector<int> a(n);
    rep(i,0,n){
        a[i]=read();
    }
    fenwick_tree<int> fw(n+1);
    fw.add(0,a[0]);
    rep(i,1,n){
        fw.add(i,a[i]-a[i-1]);
    }
    rep(i,0,m){
        int op=read();
        if(op==1){
            int x=read(),y=read(),k=read();
            fw.add(x-1,k);
            fw.add(y,-k);
        }
        else{
            int x=read();
            print(fw.sum(0,x));
        }
    }
    
}

signed main()
{
    IO(solve);
    return 0;
}