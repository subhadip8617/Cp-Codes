#include<bits/stdc++.h>
using namespace std;
#define int long long

string bin(int n){
    string s;
    while(n){
        if(n%2){
            s.push_back('1');
        }
        else{
            s.push_back('0');
        }
        n/=2;
    }
    reverse(s.begin(),s.end());
    return s;
}

int dec(string b){
    int x=0;
    reverse(b.begin(),b.end());
    for(int i=0;i<b.size();i++){
        if(b[i]=='1')
            x+=(1LL<<i);
    }
    return x;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n=6;
    cout<<bin(n);

    return 0;
}
