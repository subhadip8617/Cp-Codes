
#include<bits/stdc++.h>
using namespace std;
#define int long long

// finds x and y such that a * x + b * y = c

template<typename T>
pair<T, T> egcd(T a, T b, T c) {
    if (a == 0) {
        // b * y = c
        assert(c % b == 0);
        return {0, c / b};
    }
    // a * x + b * y = c
    // a * x + (b % a + (b/a) * a) * y = c
    // a * (x + (b/a) * y) + (b % a) * y = c
    auto [y0, x0] = egcd(b % a, a, c);
    T y = y0;
    T x = x0 - (b / a) * y;
    return {x, y};
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a=5,b=3,c=10;
    auto p=egcd<int>(a,b,c);
    cout<<p.first<<" "<<p.second;

    return 0;
}
