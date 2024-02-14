#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void prd(const T& x);
template <typename T, typename U>
    void prd(const pair<T, U>& val);
template <typename T, typename... Args>
    void prd(const T& val, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& cont);
template <typename T>
    void debug(const set<T>& cont);
template <typename T>
    void debug(const vector<T>& cont);
template <typename T>
    void debug(const vector<vector<T>> &cont);

const int MOD = 1e9 + 7;
const int MOD_INV = 1e9 + 6;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFLL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<const int &M = MOD>
struct _mint {
    int val;

    _mint(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend _mint power(_mint a, ll b){_mint c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend _mint power(_mint a, const _mint b){return power(a, b.val);}
    friend _mint inv(_mint a){return power(a, M - 2);}

    _mint& operator+=(const _mint &b){val += b.val; if (val >= M) val -= M; return *this;}
    _mint& operator-=(const _mint &b){val -= b.val; if (val < 0) val += M; return *this;}
    _mint& operator*=(const _mint &b){val = (ll)val * b.val % M; return *this;}
    _mint& operator/=(const _mint &b){return *this *= inv(b);}
    _mint& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    _mint& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    _mint operator++(int){_mint a = *this; ++*this; return a;}
    _mint operator--(int){_mint a = *this; --*this; return a;}

    friend _mint operator-(const _mint &a){return 0 - a;}
    friend _mint operator+(const _mint &a, const _mint &b){return _mint(a) += b;}
    friend _mint operator-(const _mint &a, const _mint &b){return _mint(a) -= b;}
    friend _mint operator*(const _mint &a, const _mint &b){return _mint(a) *= b;}
    friend _mint operator/(const _mint &a, const _mint &b){return _mint(a) /= b;}
    
    friend bool operator==(const _mint &a, const _mint &b){return a.val == b.val;}
    friend bool operator!=(const _mint &a, const _mint &b){return a.val != b.val;}
    friend bool operator>=(const _mint &a, const _mint &b){return a.val >= b.val;}
    friend bool operator<=(const _mint &a, const _mint &b){return a.val <= b.val;}
    friend bool operator>(const _mint &a, const _mint &b){return a.val > b.val;}
    friend bool operator<(const _mint &a, const _mint &b){return a.val < b.val;}
    
    friend std::ostream& operator<<(std::ostream& os, const _mint &a){return os << a.val;}
    friend std::istream& operator>>(std::istream& is, _mint &a){return is >> a.val;}
};
using mint = _mint<>;

int main(){
 
    FastIO();
    int n, a; cin >> n;
    mint p, num = 1, sum = 1, prod = 1;
    _mint<MOD_INV> sq = 1;
    for(int i = 0; i < n; i++){
        cin >> p >> a;

        num *= (a + 1);
        sum *= (power(p, a + 1) - 1) / (p - 1); 
        prod = power(prod, a + 1) * power(power(p, 1LL * a * (a + 1) / 2), sq.val);
        sq *= (a + 1);
    }

    cout << num << ' ' << sum << ' ' << prod << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& val){ cerr << "("; prd(val.first); cerr << ", "; prd(val.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& val, Args... args){prd(val); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
