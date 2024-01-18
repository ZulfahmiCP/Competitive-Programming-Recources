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
int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<int> A(n);
    vector<ll> sum(4*n);

    for(int &a : A)
        cin >> a;
    
    function<void(int, int, int)> build = [&](int pos, int l, int r) -> void {
        if(l == r){
            sum[pos] = A[l];
            return;
        }

        int m = (l + r)/2;
        build(2*pos + 1, l, m);
        build(2*pos + 2, m + 1, r);

        sum[pos] = sum[2*pos + 1] + sum[2*pos + 2];
    };

    function<ll(int, int, int, int, int)> get_sum = [&](int pos, int l, int r, int L, int R) -> ll {
        if(l > R || r < L)
            return 0;

        if(L <= l && r <= R)
            return sum[pos];
        
        int m = (l + r)/2;
        return get_sum(2*pos + 1, l, m, L, R) + get_sum(2*pos + 2, m + 1, r, L, R);
    };

    function<void(int, int, int, int, int)> update = [&](int pos, int l, int r, int index, int val) -> void {
        if(l == r){
            sum[pos] = val;
            return;
        }

        int m = (l + r)/2;
        if(index <= m)
            update(2*pos + 1, l, m, index, val);
        else 
            update(2*pos + 2, m + 1, r, index, val);
        
        sum[pos] = sum[2*pos + 1] + sum[2*pos + 2];
    };

    build(0, 0, n - 1);

    for(int i = 0, t,a,b; i < q; i++){
        cin >> t >> a >> b;

        if(t == 1)
            update(0, 0, n - 1, a - 1, b);
        else 
            cout << get_sum(0, 0, n - 1, a - 1, b - 1) << '\n';
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
