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
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void prd(const T& x);
template <typename T, typename U>
    void prd(const pair<T, U>& value);
template <typename T, typename... Args>
    void prd(const T& value, Args... args);
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
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const int N = 1e7;
const double EPS = 1e-9;

void FastIO();

struct Factor {
    int N;
    vector<int> mind;

    Factor(int n) : N(n) {
        mind.resize(N + 1, -1);

        mind[1] = 1;

        for(int i = 2; i <= N; i++) if(mind[i] == -1)
            for(int j = i; j <= N; j += i)
                if(mind[j] == -1)
                    mind[j] = i;
    }

    vector<pair<int, int>> fac(int n) {
        vector<pair<int, int>> div;

        while(n > 1){
            if(div.empty() || div.back().fi != mind[n])
                div.pb({mind[n], power(n, mind[n])});
            n /= mind[n];
        }

        return div;
    }

    vector<int> prime_div(int n) {
        vector<int> div;

        while(n > 1){
            if(div.empty() || div.back() != mind[n])
                div.pb(mind[n]);
            n /= mind[n];
        }

        return div;
    }

    int power(int n, int p){
        if(n % p) return 0;
        return 1 + power(n / p, p);
    }
};

int main(){
 
    FastIO();
    int n; cin >> n;
    vector<pair<int, int>> ans(n, {-1, -1});
    Factor F(N);

    for(int i = 0, x; i < n; i++){
        cin >> x;
        auto prime = F.prime_div(x);

        if(sz(prime) == 1) 
            continue;

        ans[i].fi = prime[0], ans[i].se = 1;
        for(const int &p : prime)
            if(p != prime[0])
                ans[i].se *= p;
    }

    for(int i = 0; i < n; i++)
        cout << ans[i].fi << " \n"[i == n - 1];
    for(int i = 0; i < n; i++)
        cout << ans[i].se << " \n"[i == n - 1];

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
