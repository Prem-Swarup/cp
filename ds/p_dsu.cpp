#include<bits/stdc++.h>
using namespace std;

class pdsu {
public:
    vector<int> rnk, prnt, vrsn;
    pdsu(int n): rnk(n, 0), prnt(n), vrsn(n, INT_MAX) {
        for (int i = 0; i < n; i++) {
            prnt[i] = i;
        }
    }

    int find(int x, int t) {
        if (prnt[x] == x || vrsn[x] >= t) {
            return x;
        }
        return find(prnt[x], t);
    }

    bool unionSet(int a, int b, int t) {
        int pa = find(a, INT_MAX);
        int pb = find(b, INT_MAX);
        if (pa == pb) {
            return false;
        }
        if (rnk[pa] > rnk[pb]) {
            vrsn[pb] = t;
            prnt[pb] = pa;
        } else {
            vrsn[pa] = t;
            prnt[pa] = pb;
            if (rnk[pa] == rnk[pb]) {
                rnk[pb]++;
            }
        }
        return true;
    }
};
