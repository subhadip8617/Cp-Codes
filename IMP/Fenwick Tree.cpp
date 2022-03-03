#include<bits/stdc++.h>
using namespace std;
#define int long long

template <typename TYPE>
class FenwickTree
{
    private:
        TYPE * add;
        TYPE * mul;
        size_t length;

        // performs the actual range update
        void range_update_helper(size_t pos, TYPE mulfact, TYPE addfact)
        {
            pos += 1;
            while(pos <= length)
            {
                mul[pos - 1] += mulfact;
                add[pos - 1] += addfact;
                pos += pos & -pos;
            }
        }

    public:
        // constructor with vector
        FenwickTree(std::vector<TYPE>& v)
        {
            length = v.size();
            add = new TYPE[length];
            mul = new TYPE[length];

            // initialize
            for(size_t i = 0; i < length; ++i)
            {
                add[i] = 0;
                mul[i] = 0;
            }

            // point-wise updates
            for(size_t i = 0; i < length; ++i)
            {
                point_update(i, v[i]);
            }
        }

        // constructor with an array v[] of given size input_length
        FenwickTree(TYPE v[], int input_length)
        {
            length = input_length;
            add = new TYPE[length];
            mul = new TYPE[length];

            // initialize
            for(size_t i = 0; i < length; ++i)
            {
                add[i] = 0;
                mul[i] = 0;
            }

            // point-wise updates
            for(size_t i = 0; i < length; ++i)
            {
                point_update(i, v[i]);
            }
        }

        // add value 'val' to position i in a[0..length - 1]
        void point_update(size_t i, TYPE val)
        {
            range_update(i, i, val);
        }

        // add value 'val' to postions a[i..j]
        void range_update(size_t i, size_t j, TYPE val)
        {
            if(i < 0 or j < i or j >= length)
            {
                throw std::invalid_argument("subarray range invalid.");
            }
            else
            {
                range_update_helper(i, val, -val * ((TYPE) i - 1));
                range_update_helper(j, -val, val * j);
            }
        }

        // find sum of range a[i..j] (both inclusive)
        TYPE range_sum(size_t i, size_t j)
        {
            if(i < 0 or j < i or j >= length)
            {
                throw std::invalid_argument("subarray range invalid.");
            }
            else
            {
                if(i > 0)
                {
                    return prefix_sum(j) - prefix_sum(i - 1);
                }
                else
                {
                    return prefix_sum(j);
                }
            }
        }

        // find sum of range a[0..i] (both inclusive)
        TYPE prefix_sum(size_t i)
        {
            TYPE mulfact = 0;
            TYPE addfact = 0;

            size_t startindex = i;
            i += 1;

            while(i > 0)
            {
                addfact += add[i - 1];
                mulfact += mul[i - 1];
                i = i & (i - 1);
            }

            return ((TYPE) startindex) * mulfact + addfact;
        }

        // returns the value of a[i]
        TYPE point_sum(size_t i)
        {
            if(i < 0 or i >= length)
            {
                throw std::invalid_argument("invalid array index.");
            }
            else
            {
                return range_sum(i, i);
            }
        }

};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> vec={1,2,3,4,5};
    FenwickTree<int> tree(vec);
    cout<<tree.range_sum(0,3)<<"\n";
    tree.range_update(0,2,1);
    cout<<tree.range_sum(0,3)<<"\n";

    return 0;
}
