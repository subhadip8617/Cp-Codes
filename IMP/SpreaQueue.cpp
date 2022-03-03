#include<bits/stdc++.h>
using namespace std;
#define int long long

template<class T, T e, typename F>
class SpreadQueue
{
    int size;
    T in;
    F f;
    stack<T> out, val_in, val_out;

public:
    template<typename G>
    SpreadQueue(G&& g): f(forward<G>(g)), size(0), in(e)
    {
        out.push(e);
    }

    void push(T v)
    {
        val_in.push(v);
        in = f(in, v);
        size++;
    }

    void pop()
    {
        if(val_out.empty())
        {
            while(!val_in.empty())
            {
                val_out.push(val_in.top());
                val_in.pop();
                out.push(f(val_out.top(), out.top()));
            }
            in = e;
        }
        out.pop();
        val_out.pop();
        assert(size--);
    }

    T best() const
    {
        return empty()? e : f(in, out.top());
    }

    bool empty() const
    {
        return !size;
    }
};

template<class T, T e, typename F>
auto make_SpreadQueue(F&& f)
{
    return SpreadQueue<T, e, decltype(f)> (forward<F>(f));
}

int func(int a,int b)
{
    return a+b;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto q=make_SpreadQueue<int,0LL>(func);
    q.push(6);
    q.push(2);
    cout<<q.best()<<"\n";
    q.pop();
    q.push(12);
    cout<<q.best()<<"\n";

    return 0;
}
