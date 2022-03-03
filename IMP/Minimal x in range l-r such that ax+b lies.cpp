#include<bits/stdc++.h>
using namespace std;
#define int long long

// returns minimal x such that a*x+b \in [l; r] % mod
// l and r don't have to be in [0, mod) (see first couple of lines for understanding)
// O(log(mod))
int first_in_range(int a, int b, int l, int r, int mod, int no_solution_return = 4e18) {
    r -= b; l -= b;
    int dif = r - l;
    if (dif >= mod) return 0;
    if (dif < 0) return no_solution_return;
    l = (l % mod + mod) % mod;
    r = (r % mod + mod) % mod;

    int g = gcd(a, mod);
    const int inf = 4e18;

    auto get_inv = [&](int a, int mod) -> int {
        int b = mod, x = 0, y = 1;
        while (a != 0) {
            int k = b / a;
            b -= k * a; x -= k * y;
            swap(a, b); swap(x, y);
        }
        x %= mod;
        if (x < 0) x += mod;
        return x;
    };

    auto solve_internal = [&](int mod, int l, int r, int a) -> int {
        if (a == 0) return (l == 0 ? 0 : inf);
        a /= g;
        mod /= g;
        r /= g;
        l = (l + g - 1) / g;
        if (l > r) return inf;
        if (mod == 1) return 0;

        a = get_inv(a, mod);
        int b = l * a % mod;
        int k = r - l;

        int b0 = b;
        int mod0 = mod;
        int ainv = get_inv(a, mod);

        auto get_steps = [&](int t, int ia, int b, int m) -> int {
            return (t - b + m) % m * ia % m;
        };

        while (true) {
            if (a == 0) return b;
            if (a < mod - a) {
                int b1 = (b < a ? b : ((b - mod) % a + a) % a);

                if (get_steps(b1, ainv, b0, mod0) > k) return b;

                int a1 = ((-mod) % a + a) % a;
                int m1 = a;

                a = a1;
                b = b1;
                mod = m1;
            } else {
                int a1 = a % (mod - a);
                int b1 = b % (mod - a);
                int m1 = mod - a;

                int steps = get_steps(b1, ainv, b0, mod0);
                if (steps > k) {
                    int div = steps - get_steps(b1 + m1, ainv, b0, mod0);
                    return b1 + m1 * ((steps - k + div - 1) / div);
                }

                a = a1;
                b = b1;
                mod = m1;
            }
        }
    };

    int res;
    if (l <= r) {
        res = solve_internal(mod, l, r, a);
    } else {
        res = min(solve_internal(mod, 0, r, a), solve_internal(mod, l, mod - 1, a));
    }
    if (res == inf) res = no_solution_return;
    return res;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a=5,b=3,l=10,r=1e9,m=1e9+7;
    int x=first_in_range(a,b,l,r,m);
    cout<<x;

    return 0;
}

