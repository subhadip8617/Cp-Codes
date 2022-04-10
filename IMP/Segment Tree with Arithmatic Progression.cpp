#include<bits/stdc++.h>
using namespace std;
#define int long long

struct item{
    int left, step;
};

struct SegTree{
    int sz;
    vector<item> values;
    vector<int> add;

    //-----<Set up the neutral element, single, and merge for current item>-----//

    item NEUTRAL_ELEMENT = {0LL, 0LL};
    int NO_OP = 0;

    void prop(int x, int lx, int rx){
        if(rx - lx == 1) return;
        int len = (rx - lx) /2;

        //propogate add
        add[2*x + 1] += add[x];
        add[2*x + 2] += add[x];
        add[x] = 0;

        //left child
        values[2*x + 1].left += values[x].left;
        values[2*x + 1].step += values[x].step;

        //right child
        values[2*x + 2].left += (values[x].left + (len* values[x].step));
        values[2*x + 2].step += values[x].step;

        //self
        values[x].left = 0;
        values[x].step = 0;
        return;
    }


    //-----</Set up the neutral element, single, and merge for current item>-----//

    void init(int n){
        sz = 1;
        while(sz < n) sz*=2;
        values.assign(sz*2, NEUTRAL_ELEMENT);
        add.assign(sz*2, 0LL);
        return;
    }

    void modify_range(int l, int r, int a, int v, int x, int lx, int rx){
        prop(x, lx, rx);
        if(r <= lx || l >= rx) return;

        if(lx >= l && rx <= r){
            add[x] += a;
            values[x].step += v;
            values[x].left += (v * (lx - l));
        //  debug() << exp(lx) << exp(rx) << exp(l) << exp(v) << exp(v*(lx-l));
            return;
        }

        int m = lx + (rx - lx)/2;
        modify_range(l, r, a, v, 2*x + 1, lx, m);
        modify_range(l, r, a, v,2*x + 2, m, rx);
        return;
    }

    void modify_range(int l, int r, int a, int v){
        modify_range(l, r, a, v,0, 0, sz);
        return;
    }

    int pos_value(int i, int x, int lx, int rx){
        prop(x, lx, rx);

        if(rx - lx == 1){
            return (values[x].left + add[x]);
        }

        int m = lx + (rx - lx) / 2;

        if(m <= i){
            return pos_value(i, 2*x + 2, m, rx);
        }else{
            return pos_value(i, 2*x + 1, lx, m);
        }
    }

    int pos_value(int i){
        return pos_value(i, 0, 0, sz);
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n=10;
    SegTree st;
    st.init(n);
    // modify range(l,r,start,+=x)
    // start start+x start+2x start+3x
    st.modify_range(0,5,1,5);
    for(int i=0;i<n;i++){
        cout<<st.pos_value(i)<<" ";
    }

    return 0;
}
