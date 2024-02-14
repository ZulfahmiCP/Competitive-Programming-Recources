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
const ll INFLL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct SegTree {
    int N;
    vector<int> arr, tree;

    SegTree(const vector<int> &A) : arr(A), N(sz(A)), tree(4 * N) {
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = gcd(tree[2 * x + 1], tree[2 * x + 2]);
    }

    int calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    int process(int x, int l, int r, int ql, int qr) {
        if(l > qr || r < ql)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x];
        
        int m = (l + r) >> 1;
        
        return gcd(process(2 * x + 1, l, m, ql, qr), 
                   process(2 * x + 2, m + 1, r, ql, qr));
    }
};

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        vector<int> A(n);

        for(int &a : A)
            cin >> a;
        for(int i = 0; i < n; i++)
            A.pb(A[i]);

        SegTree seg(A);

        auto good = [&](int x) -> bool {
            for(int i = 0, prev = -1, cur; i < n; i++, prev = cur){
                cur = seg.calc(i, i + x);
                if(prev != -1 && cur != prev)
                    return 0;
            }

            return 1;
        };

        function<int(int, int)> bin_search = [&](int l, int r) -> int {
            if(l == r)
                return l + 1;
            
            int m = (l + r + 1) >> 1;

            if(good(m)) 
                return bin_search(l, m - 1);
            return bin_search(m, r);
        };
        
        cout << (good(0) ? 0 : bin_search(0, n - 1)) << '\n';
    }    

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
