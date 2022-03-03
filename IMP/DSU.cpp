#include<bits/stdc++.h>
using namespace std;
#define int long long

struct DSU
{
	int connected;
	vector<int> par,sz;

	DSU() {}

	DSU(int n)
	{
	    par.resize(n+1);
	    sz.resize(n+1);
		for(int i=1;i<=n;i++)
		{
			par[i]=i;
			sz[i]=1;
		}
		connected=n;
	}

	int getPar(int k)
	{
		while(k!=par[k])
		{
			par[k]=par[par[k]];
			k=par[k];
		}
		return k;
	}

	int getSize(int k)
	{
		return sz[getPar(k)];
	}

	void unite(int u, int v)
	{
		int par1=getPar(u), par2=getPar(v);

		if(par1==par2)
			return;

		connected--;

		if(sz[par1]>sz[par2])
			swap(par1, par2);

		sz[par2]+=sz[par1];
		sz[par1]=0;
		par[par1]=par[par2];
	}
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    DSU d(5);
    d.unite(1,5);
    cout<<d.getSize(1);

    return 0;
}
