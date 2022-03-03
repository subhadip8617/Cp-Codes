#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;
const long long MOD2 = static_cast<long long>(MOD) * MOD;

struct Matrix
{
    vector< vector<int> > mat;
    int n_rows, n_cols;

    Matrix() {}

    Matrix(vector< vector<int> > values): mat(values), n_rows(values.size()),
        n_cols(values[0].size()) {}

    static Matrix identity_matrix(int n)
    {
        vector< vector<int> > values(n, vector<int>(n, 0));
        for(int i = 0; i < n; i++)
            values[i][i] = 1;
        return values;
    }

    Matrix operator*(const Matrix &other) const
    {
        int n = n_rows, m = other.n_cols;
        vector< vector<int> > result(n_rows, vector<int>(n_cols, 0));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                long long tmp = 0;
                for(int k = 0; k < n_cols; k++) {
                    tmp += mat[i][k] * 1ll * other.mat[k][j];
                    while(tmp >= MOD2)
                        tmp -= MOD2;
                }
                result[i][j] = tmp % MOD;
            }

        return move(Matrix(move(result)));
    }

    inline bool is_square() const
    {
        return n_rows == n_cols;
    }
};

// binary exponentiation, returns a^p
Matrix pw(Matrix a,int p){
    Matrix result = Matrix::identity_matrix(a.n_cols);
    while (p > 0) {
        if (p & 1)
            result = a * result;
        a = a * a;
        p >>= 1;
    }
    return result;
}

//N'TH FIBONACCI NUMBER IN O(logN)
/*
    dp[n]=dp[n-1]+dp[n-2]

   [1,1]   dp[n-1]     dp[n]
   [1,0]   dp[n-2]     dp[n-1]
*/

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    if(n==0 || n==1)
    {
        cout<<n;
        return 0;
    }
    Matrix m({
            {1,1},
            {1,0}
        });
    Matrix v({
            {1},
            {0}
        });
    Matrix res=pw(m,n-1)*v;  //for nth multiply it n-1 times
    cout<<res.mat[0][0];

    return 0;
}

