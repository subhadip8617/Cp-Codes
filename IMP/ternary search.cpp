#include<bits/stdc++.h>
using namespace std;
#define int long long

double f(double x)
{
    return -1;
}

// DECREASE->LOWEST POINT->INCREASE
double ternary_search(double l, double r) {
    for(int i=0;i<90;i++)
    {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if(f(m1)>f(m2))
            l=m1;
        else
            r=m2;
    }
    return f(l);
}

//INCREASE->HIGHEST POINT ->DECREASE
double ternarysearch(double l, double r) {
    for(int i=0;i<90;i++)
    {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if(f(m1)<f(m2))
            l=m1;
        else
            r=m2;
    }
    return f(l);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    return 0;
}

