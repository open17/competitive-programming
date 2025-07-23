// #define REAP_READ
// #define USE_LL
// #define USE_IOS
// #define IN_FILE "data.in"
// #define OUT_FILE "solve.out"
#define USE_STD
#include <bits/stdc++.h>
#include "template.h"
#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace atcoder;

const int N = 5e5 + 5;
const int MOD = 571373;
using mint = modint;

struct S
{
    mint sum;
    int len;
};

S op(S a, S b)
{
    return {a.sum + b.sum, a.len + b.len};
}

S e()
{
    return {mint(0), 0};
}

struct F
{
    mint mult;
    mint add;
};

F composition(F new_f, F old_f)
{
    return {new_f.mult * old_f.mult, new_f.mult * old_f.add + new_f.add};
}

F id()
{
    return {mint(1), mint(0)};
}

S mapping(F f, S x)
{
    return {x.sum * f.mult + f.add * x.len, x.len};
}

void solve()
{
    int n = read(), q = read(), m=read();
    mint::set_mod(m);
    vector<S> v(n, {0, 1});
    rep(i, 0, n) v[i].sum = read();
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
    rep(i, 0, q)
    {
        int op = read();
        int x = read(), y = read();
        if (op == 1)
        {
            mint k = read();
            seg.apply(x - 1, y, F{k,mint(0)});
        }
        else if(op==2){
            mint k = read();
            seg.apply(x - 1, y, F{mint(1),k});
        }
        else
        {
            print(seg.prod(x - 1, y).sum.val());
        }
    }
}

signed main()
{
    IO(solve);
    return 0;
}