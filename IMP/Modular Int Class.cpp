#include<bits/stdc++.h>
using namespace std;
#define int long long

const int32_t MOD = 1e9+7;
struct mod_int {
    int32_t val;
    mod_int(long long v = 0) {if (v < 0) v = v % MOD + MOD; if (v >= MOD) v %= MOD; val = v; }

    static int32_t mod_inv(int32_t a, int32_t m = MOD) {
        int32_t g = m, r = a, x = 0, y = 1;
        while (r != 0) {
            int32_t q = g / r;
            g %= r; swap(g, r);
            x -= q * y; swap(x, y);
        }
        return x < 0 ? x + m : x;
    }
    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
        #if !defined(_WIN32) || defined(_WIN64)
        return x % m;
        #endif
        unsigned x_high = x >> 32, x_low = (unsigned) x;
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }

    explicit operator int() const {return val; }
    mod_int& operator+=(const mod_int &other) {val += other.val; if (val >= MOD) val -= MOD; return *this; }
    mod_int& operator-=(const mod_int &other) {val -= other.val; if (val < 0) val += MOD; return *this; }
    mod_int& operator*=(const mod_int &other) {val = fast_mod((uint64_t) val * other.val); return *this; }
    mod_int& operator/=(const mod_int &other) {return *this *= other.inv(); }
    friend mod_int operator+(const mod_int &a, const mod_int &b) { return mod_int(a) += b; }
    friend mod_int operator-(const mod_int &a, const mod_int &b) { return mod_int(a) -= b; }
    friend mod_int operator*(const mod_int &a, const mod_int &b) { return mod_int(a) *= b; }
    friend mod_int operator/(const mod_int &a, const mod_int &b) { return mod_int(a) /= b; }
    mod_int& operator++() {val = val == MOD - 1 ? 0 : val + 1; return *this; }
    mod_int& operator--() {val = val == 0 ? MOD - 1 : val - 1; return *this; }
    mod_int operator++(int32_t) { mod_int before = *this; ++*this; return before; }
    mod_int operator--(int32_t) { mod_int before = *this; --*this; return before; }
    mod_int operator-() const {return val == 0 ? 0 : MOD - val; }
    bool operator==(const mod_int &other) const { return val == other.val; }
    bool operator!=(const mod_int &other) const { return val != other.val; }
    mod_int inv() const {return mod_inv(val); }
    friend ostream& operator<<(ostream &stream, const mod_int &m) {return stream << m.val; }
    friend istream& operator>>(istream &stream, mod_int &m) {return stream >> m.val; }

    mod_int pow(long long p) const {
        assert(p >= 0);
        mod_int a = *this, result = 1;
        while (p > 0) {
            if (p & 1)
                result *= a;

            a *= a;
            p >>= 1;
        }
        return result;
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mod_int m=213;
    cout<<m/2;

    return 0;
}
