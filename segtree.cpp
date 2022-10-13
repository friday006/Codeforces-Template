#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define ll long long int
#define ld long int
#define nl "\n"
#define ss second
#define ff first
using namespace std;

ll MOD = 1000000007;
/*------------------------------------For Debugging-------------------------------------------------------------------------*/
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x<<" "; _print(x); cerr << nl;
#else
#define debug(x...)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(double t) {cerr << t;}

template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
/*-------------------------------------------------------------------------------------------------------------------------*/
bool comp(const pair<pair<int, int>,int> &a, const pair<pair<int, int>,int> &b) { return (a.second < b.second); }
bool isPowerOfTwo(int n)   {if (n == 0)       return false;return (ceil(log2(n)) == floor(log2(n)));}
double abaseb(int a, int b)  {return log2(a) / log2(b);}
bool isPowerOfThree(int n)  {if (n == 0) return false; cout << abaseb(n, 3) << nl;int num1 = ceil(abaseb(n, 3));
                  int num2 = floor(abaseb(n, 3));if (num1 == num2)    return true;  else return false;}
ll lcm(ll a, ll b) { return (a / __gcd(a, b)) * b; }
ll countDivisors(ll n)
{ ll cnt = 0;for (ll i = 1; i <= sqrt(n); i++) {
        if (n % i == 0){ if (n / i == i) cnt++;
        else  cnt = cnt + 2; } }
    return cnt;
}
bool isPrime(ll n)
{ if (n <= 1) return false;
  for (int i = 2; i * i <= n; i++)      if (n % i == 0){ return false;}
    return true;
}
string bin(ll n){
    ll i;string val = "0";
    for (i = 1 << 30; i > 0; i = i / 2)
    { if((n & i) != 0) { val+="1"; }
    else { val+="0"; } }
    while(val.front()=='0'){ val.erase(0,1); }
    return val;
}
ll DivOrNot(ll n1, ll n2){ if(n1 % n2 == 0)  return n1/n2; else return (n1/n2)+1;}
ll is_string_palindrome(string b){ string n = b; reverse(all(n)); if(n==b) return 1;return 0;}
/*----------------------------------------Template Ends-----------------------------------------------------------------*/

struct segtree{
    ll size;
    vector<ll> sums;
    /*Initializing the sums vector size(or we can say segtree)*/
    void init(int n){
        size = 1;
        while(size<n){
            size*=2;
        }
        sums.assign(2*size,0LL);
    }
    /*build part2 -> here we use recursion to iterate over segtree
     and add the value of array to the leaf */
    void build2(vector<ll> &a,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            if(lx<a.size()){
                sums[x] = a[lx];
            }
            return;
        }
        ll m = (lx+rx)/2;
        build2(a,2*x+1,lx,m);
        build2(a,2*x+2,m,rx); 
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    /* assigning the values of given vector to segtree*/
    void build(vector<ll> &a){
        build2(a,0,0,size);
    }


    /* setting a particluar value of leaf node of segtree */
    void set(ll i ,ll v,ll x,ll lx,ll rx){
        if(rx-lx == 1){
            sums[x] = v;
            return;
        }
        ll m = (lx+rx)/2;
        if(i<m){
        set(i,v,2*x+1,lx,m);
        }
        else{
        set(i,v,2*x+2,m,rx); 
        }
        sums[x] = sums[2*x+1] + sums[2*x+2];
    }

    void set(ll i,ll v){
        set(i,v,0,0,size);
    }



    /* finding sum now */
    ll sum(ll l ,ll r,ll x,ll lx,ll rx){
        /* if the whole segment is outside the limits then return 0 */
        if(lx>=r || rx<=l){
            return 0;
        }
        /* if the whole segment is inside our limits pick all*/
        else if(lx>=l && rx<=r){
            return sums[x];
        }
        /* else perform recursion to iterate over it and find the sum of particular leaf
        */
        ll m = (lx+rx)/2;
        ll s1 = sum(l,r,2*x+1,lx,m);
        ll s2 = sum(l,r,2*x+2,m,rx); 
        return s1+s2;
        
    }

    ll sum(ll l,ll r){
        return sum(l,r,0,0,size);
    }



};



void todo()
{
    ll n,m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    vector<ll> a(n);
    for(ll i = 0;i<n;i++){
        cin >> a[i];
    }

    st.build(a);

    for(ll j = 0;j<m;j++){
        ll op;
        cin >> op;
        if(op == 1){
            ll i,v;
            cin >> i>> v;
            st.set(i,v);
        }
        else{
            ll l,r;
            cin >> l >> r;
            cout << st.sum(l,r) << nl;
        }



    }



}

int main()
{
    // Fib
    // ll fib[10005];
    // fib[0] = 0;fib[1] = 1;
    // for(ll i = 2; i <= 10005; i++){
    //    fib[i] = fib[i - 1] + fib[i - 2];}

    // Main Code
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll tt = 1;
    // cin >> tt;
    for (ll i = 1; i <= tt; i++)
    {
        // cout << "Case: " << i  << " ";
        todo();
    }

    return 0;
}