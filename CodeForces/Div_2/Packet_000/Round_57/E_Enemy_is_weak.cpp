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

void FastIO();
void FreeOpen();

struct FenwickTree {
    int N;
    vector<int> bit;
 
    FenwickTree(int n) : N(n), bit(N + 1, 0) {}
    FenwickTree(const vector<int> &A) : N(A.size()), bit(N + 1, 0) {
        for(int i = 0; i < N; i++)
            update(A[i], 1);
    }

    void build() {
    }
 
    void update(int i, int v) {
        for(; i <= N; i += i & -i) 
            bit[i] += v;
    }
 
    int calc(int i) {
        int sum = 0;
        for(; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }
 
    int calc(int l, int r) {
        return calc(r) - calc(l - 1);
    }
};

int main(){
 
    FastIO();
    int n, cur(1); cin >> n;
    vector<int> A(n), B;
    Map<int, int> who;

    for(int &a : A)
        cin >> a;
        
    B = A;
    sort(all(B));

    for(int &b : B){
        if(who.find(b) == who.end())
            who[b] = cur++;
        else        
            b = who[b];
    }

    for(int &a : A)
        a = who[a];
    
    FenwickTree fk(A), fj(n);

    ll ans = 0;
    for(int i = 0; i < n; i++){
        fk.update(A[i], -1);
        ans += 1LL * fj.calc(A[i] + 1, n) * fk.calc(1, A[i] - 1);
        fj.update(A[i], 1);
    }

    cout << ans << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
