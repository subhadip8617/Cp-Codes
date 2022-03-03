#include<bits/stdc++.h>
using namespace std;
//REMEMBER THIS
#define int int64_t

template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

template<typename T_array, typename T_compare>
int64_t count_pairs(T_array values, T_compare &&compare) {
    T_array buffer(values.size());

    return y_combinator([&](auto self, int start, int end) -> int64_t {
        if (end - start <= 1)
            return 0;

        int mid = (start + end) / 2;
        int64_t answer = self(start, mid) + self(mid, end);
        int left = start, right = mid, n = 0;

        while (left < mid || right < end)
            if (left < mid && (right == end || compare(values[left], values[right]))) {
                buffer[n++] = values[left++];
            } else {
                answer += left - start;
                buffer[n++] = values[right++];
            }

        copy(buffer.begin(), buffer.begin() + n, values.begin() + start);
        return answer;
    })(0, int(values.size()));
}

signed main() {
    int n;
    cin >> n;
    vector<int> values(n);

    for (auto &v : values)
        cin >> v;

    cout << count_pairs(values, less<int>()) << '\n';
    cout << count_pairs(values, greater<int>()) << '\n';
    cout << count_pairs(values, less_equal<int>()) << '\n';
    cout << count_pairs(values, greater_equal<int>()) << '\n';
}
