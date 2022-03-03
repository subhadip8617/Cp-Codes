#include<bits/stdc++.h>
using namespace std;
#define int long long

template<typename T, typename T_iterable>
vector<pair<T, int>> run_length_encoding(const T_iterable &items) {
    vector<pair<T, int>> encoding;
    T previous;
    int count = 0;

    for (const T &item : items)
        if (item == previous) {
            count++;
        } else {
            if (count > 0)
                encoding.emplace_back(previous, count);

            previous = item;
            count = 1;
        }

    if (count > 0)
        encoding.emplace_back(previous, count);

    return encoding;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string str="aabbbcddaa";
    auto v=run_length_encoding<char>(str);
    for(auto p:v){
        cout<<p.first<<" "<<p.second<<"\n";
    }

    return 0;
}
