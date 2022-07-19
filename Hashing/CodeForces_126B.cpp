/*
 *  Author: 2BrainCells
 *  Created on: [2022-07-17]    
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

const int N = 1e6 + 9;
ll modInverse(ll a, ll m) // calculates inverse modulo
{
    ll m0 = m;
    ll y = 0, x = 1;

    if (m == 1)
    {
        return 0;
    }

    while (a > 1)
    {
        ll q = a / m;
        ll t = m;

        m = a % m, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
    {
        x += m0;
    }

    return x;
}

ll p_pow[N]; // p_pow[i] = p^i % m
ll modIn[N]; // inverse modulo for p_pow[]
ll hash_val[N]; // prefix sum of hash values
const ll p = 31; // base
const ll m = 1e9 + 7; // mod

void compute_hash(string const& s) // precomputes hash_val
{
    hash_val[0] = s[0] - 'a' + 1;
    for (ll i = 1; i < (ll)s.size(); i++)
    {
        hash_val[i] = (hash_val[i - 1] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }
}

ll get_hash(string const& s) // returns hash value of a string s
{
    ll x = s[0] - 'a' + 1;
    for (ll i = 1; i < (ll)s.size(); i++)
    {
        x = (x + (s[i] - 'a' + 1) * p_pow[i]) % m;

    }
    return x;
}

void powCalc(ll n) // precomputes p_pow[] and hash_val[]
{
    p_pow[0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        p_pow[i] = (p * p_pow[i - 1]) % m;
        modIn[i]  =  modInverse(p_pow[i], m);
    }
}

ll query_hash(ll l, ll r) // calculates hash value of substring in range [l, r]
{
    if (r < l)
    {
        return 0;
    }
    if (l == 0)
    {
        return hash_val[r];
    }
    else
    {
        return ((((hash_val[r] - hash_val[l - 1]) + m) % m) * modIn[l]) % m;
    }
}

// if two substrings of range [l1, r1], [l2, r2] are merged it returns hash value of the merged string
ll mergeHash(ll l1, ll r1, ll l2, ll r2) 
{
    return (query_hash(l1, r1) + query_hash(l2, r2) * p_pow[r1 - l1 + 1]) % m;
}

void test() // for testing the template
{
    ll i, n, t, k, j, x = 0, y = 0;
    string str;
    cin >> str;
    n = (ll)str.size();
    powCalc(n);
    compute_hash(str);
    for (i = 0; i <= n; i++)
    {
        cout << i << " " << hash_val[i] << endl;
    }
    cout << query_hash(2, 3) << endl;
    cout << query_hash(0, 1) << endl;
    return;
}

void solve()
{
    string s; cin>>s;
    ll n=sz(s);

    powCalc(n);
    compute_hash(s);

    vector<pll> v;

    for(ll len=1; len<=n-2; len++)
    {
        ll pref=query_hash(0,len-1), suff=query_hash(n-len,n-1);
        if(pref==suff)
        {
            v.pb({len,pref});
        }
    }

    ll len=0;
    ll lo=0,hi=sz(v)-1;

    while(lo<=hi)
    {
        ll mid=(lo+hi)/2;

        ll curr=v[mid].ff;

        bool f=0;

        for(ll i=1; i<n; i++)
        {
            if(i+curr-1>=n-1)
            {
                break;
            }

            if(query_hash(i,i+curr-1)==v[mid].ss)
            {
                f=1;
                break;
            }
        }

        if(f)
        {
            lo=mid+1;
            len=v[mid].ff;
        }
        else
        {
            hi=mid-1;
        }
    }

    // debx(len);

    if(len==0)
    {
        cout<<"Just a legend"<<endl;
        return;
    }

    for(ll i=0; i<len; i++)
    {
        cout<<s[i];
    }
    cout<<endl;
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