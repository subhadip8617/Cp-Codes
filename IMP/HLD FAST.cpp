#include<bits/stdc++.h>
using namespace std;
#define int long long

/*
    0 based indexing
*/

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

// MY CUSTOMIZATION

//Enter the idempotent value
int idempotent=0;

//operation
int op(int l,int r)
{
    int res;
    res=max(l,r);
    return res;
}

struct SegmentTree {
    int n; vector<int> st;

    void init(int _n) { n = _n; st.resize(2 * _n); }
    void init(const vector<int> &a) {
        init(sz(a));
        for (int i = 0; i < n; i++) st[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) st[i] = op(st[i << 1], st[i << 1 | 1]);
    }

    int query(int l, int r) {
        int res = idempotent;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, st[l++]);
            if (r & 1) res = op(res, st[--r]);
        }
        return res;
    }

    void update(int p, int val) {
        for (st[p += n] = val; p > 1; p >>= 1) st[p >> 1] = op(st[p], st[p ^ 1]);
    }
};

template<bool VALS_IN_EDGE = false> struct HLD {
    int n, ti;
    vector<vector<int>> adj;
    vector<int> par, tin, head, dep, sza;
    SegmentTree st;

    HLD(int _n) : n(_n), ti(0), adj(_n), par(_n), tin(_n), head(_n), dep(_n), sza(_n) { st.init(_n); }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsSz(int u) {
        sza[u] = 1;
        for (int &v : adj[u]) {
            adj[v].erase(find(all(adj[v]), u)); // remove parent
            par[v] = u; dep[v] = dep[u] + 1;
            dfsSz(v);
            sza[u] += sza[v];
            if (sza[v] > sza[adj[u][0]]) swap(v, adj[u][0]); // store the heavy node at the beginning
        }
    }

    void dfsHld(int u) {
        tin[u] = ti++;
        for (int v : adj[u]) {
            head[v] = (v == adj[u][0] ? head[u] : v);
            dfsHld(v);
        }
    }

    void init(int s = 0) {
        par[s] = dep[s] = ti = 0; head[s] = s;
        dfsSz(s); dfsHld(s);
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            v = par[head[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    template<class OP> void processPath(int u, int v, OP op) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            op(tin[head[u]], tin[u]);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        op(tin[u] + VALS_IN_EDGE, tin[v]);
    }

    void updateNode(int u, int x) { st.update(tin[u], x); }

    int queryPath(int u, int v) {
        int res = idempotent;
        processPath(u, v, [this, &res](int l, int r) { res = op(res, st.query(l, r + 1)); });
        return res;
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    cin>>n>>q;
    int val[n];
    for(int i=0;i<n;i++){
        cin>>val[i];
    }
    HLD <false> hld(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        hld.addEdge(u,v);
    }
    hld.init();
    for(int i=0;i<n;i++){
        hld.updateNode(i,val[i]);
    }
    while(q--){
        int t;
        cin>>t;
        if(t==1){
            int a,b;
            cin>>a>>b;
            hld.updateNode(a-1,b);
        }
        else{
            int a,b;
            cin>>a>>b;
            cout<<hld.queryPath(a-1,b-1)<<" ";
        }
    }

    return 0;
}

