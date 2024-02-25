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
template<typename T, typename U>void prd(const pair<T, U>& value);
template<typename T, typename... Args>void prd(const T& value, Args... args);
template<typename... Args>void debug(Args... args);
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const int N = 1e6 + 5;
const double EPS = 1e-9;

void FastIO();

vector<bool> get_prime(int n) {
    vector<bool> prime(n + 1, 1);
    prime[0] = prime[1] = 1; 

    for(int i = 2; i * i <= n; i++) if(prime[i]) 
        for(int j = i * i; j <= n; j += i)
            prime[j] = 0;

    return prime;
}

int main(){
 
    FastIO();
    int t,n; cin >> t;
    auto prime = get_prime(N);
    vector<int> ans(N);

    ans[1] = 0;
    for(int i = 2; i < N; i++){
        ans[i] = ans[i - 1];
        if(prime[i])
            ans[i] = i;
    }

    ans[4] = 4;

    while(t--){
        cin >> n;
        cout << ans[n] << '\n';
    }

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& value){cerr<<"(";prd(value.first);cerr<<", ";prd(value.second);cerr<<")";}
template<typename T, typename... Args>void prd(const T& value, Args... args){prd(value);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr << "]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c) { for (const auto &v : c) debug(v); cerr << '\n';} 
