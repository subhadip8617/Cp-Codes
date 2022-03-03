#include<bits/stdc++.h>
using namespace std;
#define int long long

template<class T> struct PrefixSums {
    vector<vector<T>> sum;
    void init(const vector<vector<T>>& v) {
        int R = v.size(), C = v[0].size();
        sum.assign(R + 1, vector<T>(C + 1));
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                sum[i + 1][j + 1] = v[i][j] + sum[i + 1][j] + sum[i][j + 1] - sum[i][j];
            }
        }
    }
    T get(int X1, int Y1, int X2, int Y2) {
        X2 ++, Y2 ++;
        return sum[X2][Y2] - sum[X1][Y2]
               - sum[X2][Y1] + sum[X1][Y1];
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<int>> vec = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    PrefixSums<int> pre;
    pre.init(vec);
    cout<<pre.get(0,0,2,1);

    return 0;
}

