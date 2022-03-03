#include<bits/stdc++.h>
using namespace std;
#define int long long

#define sz(x) ((int)(x).size())
#define pb push_back

const int maxn = 1e5+5;
const int cat = 2;
long long p[cat], hashmod = 1e9 + 7;
long long pp[cat][maxn];
long long invpp[cat][maxn];
bool pcdone = 0;

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

int inv(int k)
{
    return pow(k, hashmod-2, hashmod);
}

struct Hash {
    vector<long long> h[cat], hr[cat];

    static void precalc() {
        if (pcdone) return;
        pcdone = 1;
        p[0]=599;
        p[1]=937;
        for (int i = 0; i < cat; ++i) {
            pp[i][0]=1;
        }
        for (int j = 0; j < cat; ++j) {
            for (int i = 1; i < maxn; ++i) {
                pp[j][i] = (pp[j][i - 1] * p[j]) % hashmod;
            }
        }
        invpp[0][maxn-1]=inv(pp[0][maxn-1]);
        invpp[1][maxn-1]=inv(pp[1][maxn-1]);
        for (int j = 0; j < cat; ++j) {
            for (int i = maxn-2; i >= 0; --i) {
                invpp[j][i]=invpp[j][i+1]*p[j];
                invpp[j][i]%=hashmod;
            }
        }
    }
    Hash(string s) {
        build(s);
    }
    void build(string s) {
        precalc();
        for (int i = 0; i < cat; ++i) {
            h[i].assign(sz(s),0);
            hr[i].assign(sz(s),0);
        }
        for (int i = 0; i < cat; ++i) {
            h[i][0]=pp[i][0]*s[0];
        }
        for (int j = 0; j < cat; ++j) {
            for (int i = 1; i < sz(s); ++i) {
                h[j][i]=(h[j][i-1]+pp[j][i]*s[i])%hashmod;
            }
        }
        for (int i = 0; i < cat; ++i) {
            hr[i][sz(s)-1]=pp[i][0]*s[sz(s)-1];
        }
        for (int j = 0; j < cat; ++j) {
            for (int i = sz(s) - 2; i >= 0; --i)
            {
                hr[j][i]=(hr[j][i+1]+pp[j][sz(s)-i-1]*s[i])%hashmod;
            }
        }
    }
    vector<int> subhash(int l, int r) {
        if (l < 0 || r >= sz(h[0])) {
            vector<int> dog;
            for (int i = 0; i < cat; ++i) {
                dog.pb(-2);
            }
            return dog;
        }
        if (r < l){
            vector<int> dog;
            for (int i = 0; i < cat; ++i) {
                dog.pb(-1);
            }
            return dog;
        }
        if (l == 0){
            vector<int> dog;
            for (int i = 0; i < cat; ++i) {
                dog.pb(h[i][r]);
            }
            return dog;
        }
        vector<int> dog;
        for (int i = 0; i < cat; ++i) {
            dog.pb((h[i][r] - h[i][l - 1] + hashmod) * invpp[i][l] % hashmod);
        }
        return dog;
    }
    vector<int> subhashrev(int l, int r) {
        if (l < 0 || r >= sz(h[0])) {
            vector<int> dog;
            for (int i = 0; i < cat; ++i) {
                dog.pb(-2);
            }
            return dog;
        }
        if (r < l) {
            vector<int> dog;
            for (int i = 0; i < cat; ++i) {
                dog.pb(-1);
            }
            return dog;
        }
        if (r == sz(hr[0]) - 1){
            vector<int> dog;
            for (int j = 0; j < cat; ++j) {
                dog.pb(hr[j][l]);
            }
            return dog;
        }
        vector<int> dog;
        for (int i = 0; i < cat; ++i) {
            dog.pb((hr[i][l] - hr[i][r + 1] + hashmod) * invpp[i][sz(hr[i]) - r - 1] % hashmod);
        }
        return dog;
    }
    bool ispalindrome(int l, int r) {
        return (subhash(l, r) == subhashrev(l, r));
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s="abc";
    Hash h1(s);
    auto v1=h1.subhash(0,1);
    for(auto i:v1){
        cout<<i<<" ";
    }

    return 0;
}
