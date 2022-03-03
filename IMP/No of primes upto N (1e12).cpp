#include<bits/stdc++.h>
using namespace std;
#define int long long

struct _count_primes_struct_t_ {
    vector<int> primes;
    vector<int> mnprimes;
    int ans;
    int y;
    vector<pair<pair<int, int>, char>> queries;

    void phi(int n, int a, int sign = 1) {
        if (n == 0) return;
        if (a == -1) {
            ans += n * sign;
            return;
        }
        if (n <= y) {
            queries.emplace_back(make_pair(n, a), sign);
            return;
        }
        phi(n, a - 1, sign);
        phi(n / primes[a], a - 1, -sign);
    }

    struct fenwick {
        vector<int> tree;
        int n;

        fenwick(int n = 0) : n(n) {
            tree.assign(n, 0);
        }

        void add(int i, int k) {
            for (; i < n; i = (i | (i + 1)))
                tree[i] += k;
        }

        int ask(int r) {
            int res = 0;
            for (; r >= 0; r = (r & (r + 1)) - 1)
                res += tree[r];
            return res;
        }
    };

    int count_primes(int n) {
        y = pow(n, 0.64);
        if (n < 100) y = n;
        primes.clear();
        mnprimes.assign(y + 1, -1);
        ans = 0;
        for (int i = 2; i <= y; ++i) {
            if (mnprimes[i] == -1) {
                mnprimes[i] = primes.size();
                primes.push_back(i);
            }
            for (int k = 0; k < primes.size(); ++k) {
                int j = primes[k];
                if (i * j > y) break;
                mnprimes[i * j] = k;
                if (i % j == 0) break;
            }
        }
        if (n < 100) return primes.size();
        int s = n / y;

        // pi(n) -- prime counting function
        // phi(n, a) -- number of integers from 1 to n which are not divisible by any prime from 0-th to a-th (p0=2)

        // pi(n) = phi(n, cbrt(n)) + pi(cbrt(n)) - F, where F is the number of composite number of
        // the form p*q, where p >= q >= cbrt(n) (can be counted with two pointers)

        // pi(cbrt(n))
        for (int p : primes) {
            if (p > s) break;
            ans++;
        }

        // F
        int ssz = ans;
        int ptr = primes.size() - 1;
        for (int i = ssz; i < primes.size(); ++i) {
            while (ptr >= i && (int)primes[i] * primes[ptr] > n)
                --ptr;
            if (ptr < i) break;
            ans -= ptr - i + 1;
        }

        // phi
        // store all queries phi(m, a) with m < n^2/3, calculate later with fenwick (sum in a rectangle)
        phi(n, ssz - 1);
        sort(queries.begin(), queries.end());
        int ind = 2;
        int sz = primes.size();
        // the order will be reversed, because prefix sum in a fenwick is just one query
        fenwick fw(sz);
        for (auto [na, sign] : queries) {
            auto [n, a] = na;
            while (ind <= n)
                fw.add(sz - 1 - mnprimes[ind++], 1);
            ans += (fw.ask(sz - a - 2) + 1) * sign;
        }
        queries.clear();
        return ans - 1;
    }
} _count_primes_struct_;

int count_primes(int n) {
    return _count_primes_struct_.count_primes(n);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<count_primes(3e8);

    return 0;
}

