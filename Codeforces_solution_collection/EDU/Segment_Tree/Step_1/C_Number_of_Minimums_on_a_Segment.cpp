#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <numeric>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>
#define X first 
#define Y second 
#define Int int64_t
#define pb push_back
#define pf push_front
#define ld long double
#define ll long long int
#define ull unsigned long long int
#define min_heap priority_queue<int, vector<int>, greater<int>>
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
#define Map unordered_map
#define Set unordered_set
using namespace std;
 
template <typename T>
    void printDebug(const T& x);
template <typename T, typename U>
    void printDebug(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDebug(const T& value, Args... args);
template <typename... Args>
    void Debug(Args... args);
template <typename K, typename V>
    void Debug(const map<K, V>& container);
template <typename T>
    void Debug(const set<T>& container);
template <typename T>
    void Debug(const vector<T>& container);
 
void FastIO();
void FreeOpen();
void UsacoOpen();

struct SegTree {
    int n,mx = 2e9;
    vector<int> A;
    vector<pair<int, int>> min_val;

    SegTree(int m, const vector<int> &arr) {
        n = m;
        A = arr;
        min_val.resize(4*n);
        build();
    }

    pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
        if(a.X < b.X) return a;
        if(b.X < a.X) return b;
        return {a.X, a.Y + b.Y};
    }

    void build(int pos, int l, int r) {
        if(l == r){
            min_val[pos] = {A[l], 1};
            return;
        }

        int m = (l + r)/2;
        build(2*pos + 1, l, m);
        build(2*pos + 2, m + 1, r);

        min_val[pos] = combine(min_val[2*pos + 1], min_val[2*pos + 2]);
    }

    void build() {
        build(0, 0, n - 1);
    }

    void update(int pos, int l, int r, int index, int val) {
        if(l == r){
            min_val[pos] = {val, 1};
            return;
        }

        int m = (l + r)/2;
        index <= m ? update(2*pos + 1, l, m, index, val) : update(2*pos + 2, m + 1, r, index, val);
        min_val[pos] = combine(min_val[2*pos + 1], min_val[2*pos + 2]);
    }

    void update(int index, int val) {
        update(0, 0, n - 1, index, val);
    }

    pair<int, int> query(int pos, int l, int r, int L, int R) {
        if(l > R || r < L)
            return {mx, 0};
        if(L <= l && r <= R)
            return min_val[pos];
        
        int m = (l + r)/2;
        pair<int, int> left_query = query(2*pos + 1, l, m, L, R);
        pair<int, int> right_query = query(2*pos + 2, m + 1, r, L, R);
        return combine(left_query, right_query);
    }

    pair<int, int> query(int L, int R) {
        return query(0, 0, n - 1, L, R);
    }
};  

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<int> arr(n);

    for(int &a : arr)
        cin >> a;

    SegTree A(n, arr);

    for(int i = 0, type,a,b; i < q; i++){
        cin >> type >> a >> b;

        if(type == 2){
            pair<int, int> ans = A.query(a, b - 1);
            cout << ans.X << ' ' << ans.Y << '\n';
        } else 
            A.update(a, b);
    }
    
    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args>void printDebug(const T& value, Args... args){printDebug(value); cout << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "[";  printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
