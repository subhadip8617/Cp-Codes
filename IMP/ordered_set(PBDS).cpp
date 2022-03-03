#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

signed main()
{
    ordered_set <int> s;
    s.insert(10);
    s.insert(9);
    s.insert(1);
    s.insert(7);
    s.insert(8);
    /*
    //auto does not work
    for(auto it=s.begin();it!=s.end();it++)
        cout<<*it<<" "; */

    //s={1,7,8,9,10}

    //THIS GIVES US VALUE(iterator) AT INDEX 2 like s[2]
    cout<<*s.find_by_order(2)<<"\n";
    //THIS GIVES how many element are STRICTLY LESS than 9
    cout<<s.order_of_key(9);

    return 0;
}

