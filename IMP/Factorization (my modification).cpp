#include<bits/stdc++.h>
using namespace std;
#define int long long

// ONLY REQUIRED IN C++14
// USE C++17 TO AVOID COMPILATION ERROR
int gcd(int a, int b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}

struct Factorizer {
    // Factorizer factorizer(prec_n, sp_bound, rng_seed);
    //    prec_n is the bound for sieve (inclusive)
    //    all numbers will first be checked on primes <= sp_bound (if prec_n >= sp_bound)
    //    factorization for one number ~1e18 takes ~13ms

    vector<int> min_prime;
    vector<int> primes;
    int prec_n;
    int sp_bound;

    Factorizer(int prec_n = 100, int sp_bound = 100, int rng_seed = -1) :
        prec_n(max(prec_n, 3LL)),
        sp_bound(sp_bound),
        rng(rng_seed != -1 ? rng_seed : chrono::steady_clock::now().time_since_epoch().count()) {
        min_prime.assign(prec_n + 1, -1);
        for (int i = 2; i <= prec_n; ++i) {
            if (min_prime[i] == -1) {
                min_prime[i] = i;
                primes.push_back(i);
            }
            int k = min_prime[i];
            for (int j : primes) {
                if (j * i > prec_n) break;
                min_prime[i * j] = j;
                if (j == k) break;
            }
        }
    }

    bool is_prime(int n, bool check_small = true) {
        if (n <= prec_n)
            return min_prime[n] == n;

        if (check_small) {
            for (int p : primes) {
                if (p > sp_bound || (int)p * p > n) break;
                if (n % p == 0) return false;
            }
        }

        int s = 0;
        int d = n - 1;
        while (d % 2 == 0) {
            ++s;
            d >>= 1;
        }
        for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if (a >= n) break;
            int x = mpow_long(a, d, n);
            if (x == 1 || x == n - 1)
                continue;
            bool composite = true;
            for (int i = 0; i < s - 1; ++i) {
                x = mul_mod(x, x, n);
                if (x == 1)
                    return false;
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite)
                return false;
        }
        return true;
    }

    vector<pair<int, int>> factorize(int n, bool check_small = true) {
        vector<pair<int, int>> res;
        if (check_small) {
            for (int p : primes) {
                if (p > sp_bound) break;
                if ((int)p * p > n) break;
                if (n % p == 0) {
                    res.emplace_back(p, 0);
                    while (n % p == 0) {
                        n /= p;
                        res.back().second++;
                    }
                }
            }
        }

        if (n == 1) return res;
        if (is_prime(n, false)) {
            res.emplace_back(n, 1);
            return res;
        }

        if (n <= prec_n) {
            while (n != 1) {
                int d = min_prime[n];
                if (res.empty() || res.back().first != d)
                    res.emplace_back(d, 0);
                res.back().second++;
                n /= d;
            }
            return res;
        }

        int d = get_divisor(n);
        auto a = factorize(d, false);
        for (auto &[div, cnt] : a) {
            cnt = 0;
            while (n % div == 0) {
                n /= div;
                ++cnt;
            }
        }
        auto b = factorize(n, false);

        int ia = 0, ib = 0;
        while (ia < a.size() || ib < b.size()) {
            bool choosea;
            if (ia == a.size()) choosea = false;
            else if (ib == b.size()) choosea = true;
            else if (a[ia].first <= b[ib].first) choosea = true;
            else choosea = false;

            res.push_back(choosea ? a[ia++] : b[ib++]);
        }
        return res;
    }

    vector<int> divisor(int n) {
        vector<int> vec;
        auto v = factorize(n);
        generateDivisors(0,1,v,vec);
        sort(vec.begin(),vec.end());
        return vec;
    }

private:
    mt19937_64 rng;
    int rnd(int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng);
    }

    int mpow_long(int a, int p, int mod) {
        int res = 1;
        while (p) {
            if (p & 1) res = mul_mod(res, a, mod);
            p >>= 1;
            a = mul_mod(a, a, mod);
        }
        return res;
    }

    int mul_mod(int a, int b, int mod) {
        int res = a * b - mod * (int)((long double)1 / mod * a * b);
        if (res < 0) res += mod;
        if (res >= mod) res -= mod;
        return res;
    }

    int get_divisor(int n) {
        auto f = [&](int x) -> int {
            int res = mul_mod(x, x, n) + 1;
            if (res == n) res = 0;
            return res;
        };

        while (true) {
            int x = rnd(1, n - 1);
            int y = f(x);
            while (x != y) {
                int d = gcd(n, abs(x - y));
                if (d == 0)
                    break;
                else if (d != 1)
                    return d;
                x = f(x);
                y = f(f(y));
            }
        }
    }

    void generateDivisors(int curIndex, int curDivisor,
                    vector<pair<int, int>>& arr, vector<int>& vec)
    {
        if (curIndex == arr.size()) {
            vec.push_back(curDivisor);
            return;
        }

        for (int i = 0; i <= arr[curIndex].second; ++i) {
            generateDivisors(curIndex + 1, curDivisor, arr, vec);
            curDivisor *= arr[curIndex].first;
        }
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Factorizer f(1e6, 1e18);
    auto v = f.factorize(5e17);
    for (auto p : v) {
        cout << p.first << " " << p.second << "\n";
    }
    cout << "\n";
    auto v2 = f.factorize(60);
    for (auto p : v2) {
        cout << p.first << " " << p.second << "\n";
    }
    cout<<"\n";
    auto v3=f.divisor(60);
    for(auto i:v3){
        cout<<i<<" ";
    }
    cout<<"\n";

    return 0;
}
