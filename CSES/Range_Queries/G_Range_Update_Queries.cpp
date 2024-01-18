
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
    void printDbg(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDbg(const T& value, Args... args);
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

struct FenwickTree {
    int N;
    vector<ll> BIT1, BIT2;

    FenwickTree(const vector<int>& arr) {
        N = arr.size();
        BIT1.assign(N + 1, 0);
        BIT2.assign(N + 1, 0);

        for(int i = 0; i < N; i++)
            rangeUpdate(i + 1, i + 1, arr[i]);
    }

    void update(vector<ll>& BIT, int index, ll delta) {
        for(; index <= N; index += index & -index) 
            BIT[index] += delta;
    }

    void rangeUpdate(int left, int right, ll delta) {
        update(BIT1, left, delta);
        update(BIT1, right + 1, -delta);
        update(BIT2, left, delta * (left - 1));
        update(BIT2, right + 1, -delta * right);
    }

    ll query(const vector<ll>& BIT, int index) {
        ll sum = 0;
        for(; index > 0; index -= index & -index)
            sum += BIT[index];
        return sum;
    }

    ll prefixSum(int index) {
        return query(BIT1, index) * index - query(BIT2, index);
    }

    ll rangeQuery(int left, int right) {
        return prefixSum(right) - prefixSum(left - 1);
    }

    ll query(int index) {
        return rangeQuery(index, index);
    }
};


int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<int> A(n);

    for(int &a : A)
        cin >> a;

    FenwickTree ft(A);

    for(int i = 0, t,a,b,v; i < q; i++){
        cin >> t;

        if(t == 1){
            cin >> a >> b >> v;
            ft.rangeUpdate(a, b, v);
        } else {
            cin >> v;
            cout << ft.query(v) << '\n';
        }
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
