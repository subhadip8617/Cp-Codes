#include<bits/stdc++.h>
using namespace std;

//LEETCODE PROBLEM
vector<vector<int>> ans;
void TreeAncestor(int n, vector<int>& parent)
{
    int x=log2(n);
    ans.resize(n,vector<int>(x+1,-1));
    for(int i=0; i<n; i++)
    {
        ans[i][0]=parent[i];
    }
    for(int i=1; i<=x; i++)
    {
        for(int j=0; j<n; j++)
        {
            int v=ans[j][i-1];
            if(v!=-1)
                ans[j][i]=ans[v][i-1];
        }
    }
}

int getKthAncestor(int node, int k)
{
    while(k)
    {
        int y=log2(k);
        node=ans[node][y];
        if(node<0)
            return -1;
        k-=(1<<y);
    }
    return node;
}


int main()
{


    return 0;
}
