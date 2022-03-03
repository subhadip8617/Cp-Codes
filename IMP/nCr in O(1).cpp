#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007

const int N=1e6+5;//required size

int fact[N], invfact[N];

int pow(int a, int b, int m)
{
    int ans=1;
    while(b)
    {
        if(b&1)
            ans=(ans*a)%m;
        b/=2;
        a=(a*a)%m;
    }
    return ans;
}

int modinv(int k)
{
    return pow(k, MOD-2, MOD);
}

void precompute()
{
    fact[0]=fact[1]=1;
    for(int i=2;i<N;i++)
    {
        fact[i]=fact[i-1]*i;
        fact[i]%=MOD;
    }
    invfact[N-1]=modinv(fact[N-1]);
    for(int i=N-2;i>=0;i--)
    {
        invfact[i]=invfact[i+1]*(i+1);
        invfact[i]%=MOD;
    }
}

int nCr(int x, int y)
{
    if(y>x || x<0 || y<0)
        return 0;
    int num=fact[x];
    num*=invfact[y];
    num%=MOD;
    num*=invfact[x-y];
    num%=MOD;
    return num;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    cout<<nCr(5,3);

    return 0;
}

