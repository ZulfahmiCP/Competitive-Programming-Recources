#include <bits/stdc++.h>

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
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<const int &M = MOD> struct mod_int {
    int val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inverse(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (ll)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inverse(b);}
    mod_int& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    mod_int& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    mod_int operator++(int){mod_int a = *this; ++*this; return a;}
    mod_int operator--(int){mod_int a = *this; --*this; return a;}

    friend mod_int operator-(const mod_int &a){return 0 - a;}
    friend mod_int operator!(const mod_int &a){return a.val != 0;}
    friend mod_int operator+(const mod_int &a, const mod_int &b){return mod_int(a) += b;}
    friend mod_int operator-(const mod_int &a, const mod_int &b){return mod_int(a) -= b;}
    friend mod_int operator*(const mod_int &a, const mod_int &b){return mod_int(a) *= b;}
    friend mod_int operator/(const mod_int &a, const mod_int &b){return mod_int(a) /= b;}
    
    friend bool operator==(const mod_int &a, const mod_int &b){return a.val == b.val;}
    friend bool operator!=(const mod_int &a, const mod_int &b){return a.val != b.val;}
    friend bool operator>=(const mod_int &a, const mod_int &b){return a.val >= b.val;}
    friend bool operator<=(const mod_int &a, const mod_int &b){return a.val <= b.val;}
    friend bool operator>(const mod_int &a, const mod_int &b){return a.val > b.val;}
    friend bool operator<(const mod_int &a, const mod_int &b){return a.val < b.val;}
    
    friend ostream& operator<<(ostream& os, const mod_int &a){return os << a.val;}
    friend istream& operator>>(istream& is, mod_int &a){return is >> a.val; a = mod_int(a.val);}
};
using mint = mod_int<>;

struct DiffArr {
    int N, M;
    vector<vector<ll>> A;
    vector<vector<mint>> D, dp;

    DiffArr(int n, int m) : N(n), M(m), A(N + 1, vector<ll>(M + 1, 0)), D(N + 1, vector<mint>(M + 1)), dp(N + 1, vector<mint>(M + 1)) {}

    void add_query(int r1, int c1, int r2, int c2, mint v) {
        D[r1][c1] += v;
        if(r2 + 1 <= N) D[r2 + 1][c1] -= v;
        if(c2 + 1 <= M) D[r1][c2 + 1] -= v;
        if(r2 + 1 <= N && c2 + 1 <= M) D[r2 + 1][c2 + 1] += v;
    }

    mint process() {
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= M; j++){
                D[i][j] += D[i - 1][j] + D[i][j - 1] - D[i - 1][j - 1];
                dp[i][j] = D[i][j];
                add_query(i, j, i + A[i][j], j + A[i][j], dp[i][j]);
            }
        }

        return dp[N][M];
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    DiffArr da(n, m);

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> da.A[i][j];

    da.add_query(1, 1, 1, 1, 1);
    cout << da.process() << '\n';

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
