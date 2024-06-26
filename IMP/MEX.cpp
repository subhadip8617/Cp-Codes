#include<bits/stdc++.h>
using namespace std;
#define int long long

class MEX {
  typedef std::pair<int, int> interval;
  std::set<interval> s[2];
  std::multiset<int> values;
  void insert_pair(interval p) {
    auto[x, y] = p;
    if (x > y) std::swap(x, y);
    s[0].insert({x, y});
    s[1].insert({y, x});
  }
  void remove_pair(interval p) {
    auto[x, y] = p;
    if (x > y) std::swap(x, y);
    s[0].erase({x, y});
    s[1].erase({y, x});
  }

  std::optional<interval> is_end(int x, bool left) {
    int idx = left;
    auto it = s[idx].lower_bound({x, 0});
    if (it != s[idx].end() && it->first == x)
      return *it;
    else
      return std::nullopt;
  }

 public:
  void insert(int x) {
    bool ok = values.find(x) == values.end();
    values.insert(x);
    if (!ok) return;
    auto p1 = is_end(x - 1, true);
    auto p2 = is_end(x + 1, false);
    if (p1 && p2) {
      interval i = {p1->second, p2->second};
      remove_pair(*p1);
      remove_pair(*p2);
      insert_pair(i);
    } else if (p1 && !p2) {
      interval i = {p1->second, x};
      remove_pair(*p1);
      insert_pair(i);
    } else if (!p1 && p2) {
      interval i = {x, p2->second};
      remove_pair(*p2);
      insert_pair(i);
    } else if (!p1 && !p2) {
      interval i = {x, x};
      insert_pair(i);
    }
  }
  void remove(int x) {
    values.erase(values.find(x));
    if (values.find(x) != values.end()) return;
    auto it = s[1].lower_bound({x, 0});
    if (it->first != x && it->second != x) {
      interval p1 = {it->second, x - 1};
      interval p2 = {x + 1, it->first};
      remove_pair(*it);
      insert_pair(p1);
      insert_pair(p2);
    } else if (it->first != x && it->second == x) {
      interval p = {x + 1, it->first};
      remove_pair(*it);
      insert_pair(p);
    } else if (it->first == x && it->second == x) {
      remove_pair(*it);
    } else if (it->first == x && it->second != x) {
      interval p = {it->second, x - 1};
      remove_pair(*it);
      insert_pair(p);
    }
  }
  // Find the minimum element >=x that isn't present in the set
  // If x=0 it basically finds the MEX (smallest non neg int not present)
  int get(int x=0) {
    if (values.find(x) == values.end()) return x;
    auto it = s[1].lower_bound({x, 0});
    return it->first + 1;
  }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    MEX mex;
    mex.insert(0);
    mex.insert(1);
    mex.insert(2);
    cout<<mex.get();

    return 0;
}
