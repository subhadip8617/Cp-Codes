#include<bits/stdc++.h>
using namespace std;
const int MX = 1000;

int tp[MX][MX];

void update(int x, int y, int v)
{
    for(;x<MX;x+=x&-x)
        for(int yy=y;yy<MX;yy+=yy&-yy)
            tp[x][yy]+=v;
}
int query(int x, int y)
{
    int res=0;
    for(;x>0;x-=x&-x)
        for(int yy=y;yy>0;yy-=yy&-yy)
            res+=tp[x][yy];
    return res;
}
int main()
{
    // 1 based indexing
    update(1,1,5);
    update(2,1,3);
    update(1,2,4);
    cout<<query(2,2);
}
