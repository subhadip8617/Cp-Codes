#include "bits/stdc++.h"
using namespace std;

struct node
{
    int v = 0;
    node() {}
    node(int val)
    {
        v = val;
    }
    void merge(const node &l,const node &r)  // store the thing you wanna query
    {
        // if we wanted the maximum, then we would do
        // like v = max(l.v,r.v)
        v = l.v + r.v;
    }
};

struct update
{
    int v = 0; // 4
    // use more variables if you want more information
    // these default values should be identity_transformation
    update() {}
    update(int val)
    {
        v = val; // 5
    }
    // combine the current my_update with the other my_update (see keynotes)
    void combine(update &other,const int32_t &tl,const int32_t &tr)
    {
        v += other.v; // 6
    }
    // store the correct information in the my_node x
    void apply(node &x,const int32_t &tl,const int32_t &tr)
    {
        x.v += (tr -tl +1) * v;
    }
};

//template<typename node,typename update>
struct segtree
{
    int len;
    vector<node> t;
    vector<update> u;
    vector<bool> lazy;
    node identity_element;
    update identity_transformation;
    segtree(int l)
    {
        len = l;
        t.resize(4 * len);
        u.resize(4 * len);
        lazy.resize(4 * len);
        identity_element = node();
        identity_transformation = update();
    }

    void pushdown(const int32_t &v, const int32_t &tl, const int32_t &tr)
    {
        if(!lazy[v]) return;
        int32_t tm = (tl + tr) >> 1;
        apply(v<<1,tl,tm,u[v]);
        apply(v<<1|1,tm+1,tr,u[v]);
        u[v] = identity_transformation;
        lazy[v] = 0;
    }

    void apply(const int32_t &v, const int32_t &tl, const int32_t &tr, update upd)
    {
        if(tl != tr)
        {
            lazy[v] = 1;
            u[v].combine(upd,tl,tr);
        }
        upd.apply(t[v],tl,tr);
    }

    template<typename T>
    void build(const T &arr,const int32_t &v, const int32_t &tl, const int32_t &tr)
    {
        if(tl == tr)
        {
            t[v] = arr[tl];
            return;
        }
        int32_t tm = (tl + tr) >> 1;
        build(arr,v<<1,tl,tm);
        build(arr,v<<1|1,tm+1,tr);
        t[v].merge(t[v<<1],t[v<<1|1]);
    }

    node query(const int32_t &v,const int32_t &tl,const int32_t &tr,const int32_t &l,const int32_t &r)
    {
        if(l > tr || r < tl)
        {
            return identity_element;
        }
        if(tl >= l && tr <= r)
        {
            return t[v];
        }
        pushdown(v,tl,tr);
        int32_t tm = (tl + tr) >> 1;
        node a = query(v<<1,tl,tm,l,r),b = query(v<<1|1,tm+1,tr,l,r),ans;
        ans.merge(a,b);
        return ans;
    }

    // rupd = range update
    void rupd(const int32_t &v,const int32_t &tl,const int32_t &tr,const int32_t &l,const int32_t &r,const update &upd)
    {
        if(l > tr || r < tl)
        {
            return;
        }
        if(tl >= l && tr <= r)
        {
            apply(v,tl,tr,upd);
            return;
        }
        pushdown(v,tl,tr);
        int32_t tm = (tl + tr) >> 1;
        rupd(v<<1,tl,tm,l,r,upd);
        rupd(v<<1|1,tm+1,tr,l,r,upd);
        t[v].merge(t[v<<1],t[v<<1|1]);
    }

public:
    template<typename T>
    void build(const T &arr)
    {
        build(arr,1,0,len-1);
    }
    node query(const int32_t &l,const int32_t &r)
    {
        return query(1,0,len-1,l,r);
    }
    void rupd(const int32_t &l,const int32_t &r,const update &upd)
    {
        rupd(1,0,len-1,l,r,upd);
    }
};

int main()
{
    segtree tree(1000);
    vector<int> vec(1000,10);
    vec[1]=6;
    vec[2]=5;
    tree.build(vec);
    tree.rupd(9,12,50);
    for(int i=0;i<15;i++)
        cout<<tree.query(i,i).v<<" ";

    return 0;
}

