/*
 *  Author: 2BrainCells
 *  Created on: [2022-07-18]    
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long
#define ull unsigned long long
#define pi 2*acos(0.0)
#define readl(v,n) for(ll i=0;i<n;i++) {ll val; cin>>val; v.pb(val);}
#define readi(v,n) for(int i=0;i<n;i++) {int val; cin>>val; v.pb(val);}
#define srt(v) sort(v.begin(), v.end());
#define rsrt(v) sort(v.rbegin(), v.rend());
#define MIN(v) *min_element(v.begin(), v.end())
#define MAX(v) *max_element(v.begin(), v.end())
#define sz(x) ((ll) (x).size())
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(ll i = (a); i < (b); i++)
#define rep2(i, a, b) for(ll i = (a); i <= (b); i++)
#define vll vector <ll>
#define vii vector <int>
#define pii pair <int, int>
#define pll pair <ll, ll>
#define M 1000007
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define endl "\n"
#define inf 1000000000000000000
#define ninf -1000000000000000000
#define memo(x,val) memset(x,val,sizeof(x))
#define put(n) cout<<(n)<<endl
#define toDecimal(s) bitset<64>(s).to_ullong()
#define toBinaryStr(n) bitset<64>(n).to_string()
#define toBinary(n) stoll(bitset<64>(n).to_string())

// PBDS

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using multi_ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using r_ordered_set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using r_multi_ordered_set = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<ll> s;
// s.order_of_key(k); --> number of items strictly smaller than k
// s.find_by_order(k); --> k-th item in set (0-indexing) (returns iterator)

// debugging

#define deb(n) cout<<"--"<<(n)<<"--"<<endl
#define debx(x) cout << #x << " = " << (x) << endl
#define deb2(a,b) cout<<#a<<" = "<<(a)<<", "<<#b<<" = "<<(b)<<endl
#define deb3(a,b,c) cout<<#a<<" = "<<(a)<<", "<<#b<<" = "<<(b)<<", "<<#c<<" = "<<(c)<<endl
#define debv(v) cout<<#v<<" = "; for(auto x: v) {cout<<x<<", ";} cout<<endl;
#define debv2(v) for(int i=0; i<v.size(); i++) {cout<<#v<<"["<<i<<"] = "<<v[i]<<endl;}

template<typename... T>
void debm(T&&... args) {
    ((cout << args << ", "), ...);
    cout << endl;
}

/*
    ---- take notes here ----
    
*/

const ll MAX = (1<<19) + 5;

struct info
{
    ll tup[2], indx;
    // tup[0] = rank of 1st half, tup[1] = rank of 2nd half

    bool operator < (const info& a) const
    {
        return (tup[0] != a.tup[0]) ? tup[0] < a.tup[0] : tup[1] < a.tup[1];
    }
}arr[MAX];

ll Rank[20][MAX], step;
ll LCP[MAX];
 
void build_suffix_array(const string& text)
{
    ll n = text.size(), jump;

    for(ll j = 0; j < n; j++)
    {
        // rank suffixes according to 1st char
        Rank[0][j] = text[j];

        memset(arr[j].tup, 0, sizeof(arr[j].tup));
    }

    for(step = 1, jump = 1; jump <= n; step++, jump *= 2)
    {
        for(ll j = 0; j <=n; j++)
        {
            arr[j].indx = j;

            // Rank[step - 1][j] = what was the rank of substring of length 2^(step-1) starting from jth index
            arr[j].tup[0] = Rank[step - 1][j];

            // if 2nd half exists then set the rank accordingly otherwise set rank to -1
            arr[j].tup[1] = (j + jump < n) ? Rank[step - 1][j + jump] : -1;
        }

        sort(arr, arr + n);

        Rank[step][arr[0].indx] = 0;

        for(ll j = 1; j < n; j++)
        {
            if(arr[j].tup[0] == arr[j-1].tup[0] && arr[j].tup[1] == arr[j-1].tup[1])
            {
                // if this substring is equal to previous substring then assign previous rank
                Rank[step][arr[j].indx] = Rank[step][arr[j - 1].indx];
            }
            else
            {
                // if not then assign new rank
                Rank[step][arr[j].indx] = j;
            }
        }
    }
}

void build_LCP_array(const string& text)
{
    LCP[0] = 0;
    ll n = text.size(), i, j, id1, id2;
    for(i = 1; i < n; i++)
    {
        id1 = arr[i - 1].indx;
        id2 = arr[i].indx;
        LCP[i] = 0;
        for(j = step - 1; j >= 0; j--)
        {
            if(Rank[j][id1] == Rank[j][id2] && id1 < n && id2 < n)
            {
                LCP[i] += (1 << j);
                id1 += (1 << j);
                id2 += (1 << j);
            }
        }
        // cout << arr[i - 1].indx << " " << arr[i].indx << " " << LCP[i] << endl;
    }
    // for(i = 0; i < n; i++)
    //     cout << i << " " << LCP[i] << endl;
}

ll getLCP(ll i, ll j)
{
    // return LCP of suffixes starting from i and starting from j

    // LCP(i,j) = min(LCP[pos[i]], LCP[pos[i]+1], LCP[pos[i]+2], ..., LCP[POS[j]])

    // pos[i] = position in arr[] where arr[].indx = i, this can be precalculated in an array

    // minimum in the segment can be caluclated with segment tree
}

void test()
{
    string s; cin>>s;

    s = s + "#";

    build_suffix_array(s);

    build_LCP_array(s);
}

void solve()
{
    string s; cin>>s;

    s = s+"#";

    build_suffix_array(s);

    build_LCP_array(s);

    ll ans=0;

    for(ll i=1; i<sz(s); i++)
    {
        ll len = sz(s)-arr[i].indx-1;
        ans += len - LCP[i];
    }

    cout<<ans<<endl;
}

int main()
{
    FAST
    int t = 1;
    // cin >> t;
    while(t--)
    {
        solve();    
    }

    return 0;
}