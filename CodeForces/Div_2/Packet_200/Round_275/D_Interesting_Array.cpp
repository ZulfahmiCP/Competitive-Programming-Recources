#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <cstring>
#include <numeric>
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

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void printDbg(const T& x);
template <typename T, typename U>
    void printDbg(const pair<T, U>& vue);
template <typename T, typename... Args>
    void printDbg(const T& vue, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& container);
template <typename T>
    void debug(const set<T>& container);
template <typename T>
    void debug(const vector<T>& container);
template <typename T>
    void debug(const vector<vector<T>> &container);

const int MOD = 1e9 + 7;
const int mod = 998244353;

void FastIO();
void FreeOpen();

struct SegTree {
    int N, NEUTRAL = (1 << 30) - 1;
    vector<int> arr, tree;

    SegTree(int n) : N(n), arr(N, 0), tree(4 * N) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] & tree[2 * x + 2];
    }

    int calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    int process(int x, int l, int r, int ql, int qr) {
        if(l > qr || r < ql)
            return NEUTRAL;
        if(ql <= l && r <= qr)
            return tree[x];
        
        int m = (l + r) >> 1;
        return process(2 * x + 1, l, m, ql, qr) &
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<int> sum, L(q), R(q), Q(q);
    SegTree st(n);

    for(int i = 0; i < q; i++)
        cin >> L[i] >> R[i] >> Q[i], L[i]--;
    
    for(int i = 0; i < 31; i++){
        sum = vector<int>(n + 1, 0);

        for(int j = 0; j < q; j++)
            if((Q[j] >> i) & 1)
                sum[L[j]]++, sum[R[j]]--;

        for(int j = 0; j < n; j++){
            if(j > 0) sum[j] += sum[j - 1];
            if(sum[j] > 0) st.arr[j] |= (1 << i);
        }
    }

    st.build(0, 0, n - 1);
    
    for(int i = 0; i < q; i++)
        if(st.calc(L[i], R[i] - 1) != Q[i]){
            cout << "NO\n";
            return 0;
        }

    cout << "YES\n";
    for(int i = 0; i < n; i++)
        cout << st.arr[i] << " \n"[i == n - 1];

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& vue){ cerr << "("; printDbg(vue.first); cerr << ", "; printDbg(vue.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& vue, Args... args){printDbg(vue); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
