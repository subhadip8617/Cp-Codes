#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INF 1e18

// NORMAL f FUNCTION IN DOUBLE
double f(double x)
{
    return -1;
}

// NORMAL f FUNCTION IN INT
// TAKE CARE OF LOWER BOUND AND UPPER BOUND
int f_int(int x)
{
    return -1;
}

// DECREASE->LOWEST POINT->INCREASE
int ternary_search(double l, double r) {
    double l1=l,r1=r;
    for(int i=0;i<90;i++)
    {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if(f(m1)>f(m2))
            l=m1;
        else
            r=m2;
    }
    int a=floor(l);
    int best=INF;
    for(int i=a-90;i<=a+90;i++){
        if(i<l1 || i>r1){
            continue;
        }
        best=min(best,f_int(i));
    }
    return best;
}

//INCREASE->HIGHEST POINT ->DECREASE
int ternarysearch(double l, double r) {
    double l1=l,r1=r;
    for(int i=0;i<90;i++)
    {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if(f(m1)<f(m2))
            l=m1;
        else
            r=m2;
    }
    int a=floor(l);
    int best=-INF;
    for(int i=a-90;i<=a+90;i++){
        if(i<l1 || i>r1){
            continue;
        }
        best=max(best,f_int(i));
    }
    return best;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    return 0;
}


