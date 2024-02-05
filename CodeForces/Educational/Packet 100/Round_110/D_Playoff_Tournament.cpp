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
    int N;
    string S;
    vector<int> tree, pos;

    SegTree(const string& s) : N(s.size() + 1), S(s), tree(2 * N), pos(2 * N) {
        build(0, 0, N - 1);
    }

    void merge(int x, const int &a, const int &b) {
        if(S[x] == '0')
            tree[x] = a;
        else if(S[x] == '1')
            tree[x] = b;
        else    
            tree[x] = a + b;
    }

    void build(int x, int l, int r) {
        pos[x] = l;
        if(l == r){
            tree[x] = 1;
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        merge(x, tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int j, char c){
        S[j] = c;
        upgrade(0, 0, N - 1, j);
    }

    void upgrade(int x, int l, int r, int j) {
        if(x == j){
            merge(x, tree[2 * x + 1], tree[2 * x + 2]);
            return;
        }

        if(l == r) return;

        int m = (l + r) >> 1;
        pos[j] <= m ? upgrade(2 * x + 1, l, m, j)
                    : upgrade(2 * x + 2, m + 1, r, j);

        merge(x, tree[2 * x + 1], tree[2 * x + 2]);
    }
};

int main(){
 
    FastIO();
    int n; cin >> n;
    string s; cin >> s;
    n = s.size();
    vector<int> pos(n), temp(n);

    iota(all(temp), 0);
    reverse(all(temp));
    reverse(all(s));

    for(int i = 0, j = 0; i < s.size(); i += (1 << j), j++){
        reverse(s.begin() + i, s.begin() + i + (1 << j));
        reverse(temp.begin() + i, temp.begin() + i + (1 << j));
    }

    for(int i = 0; i < n; i++)
        pos[temp[i]] = i;

    SegTree A(s);

    int q, k; cin >> q;
    while(q--){
        char c; cin >> k >> c;
        k = pos[--k];
        A.update(k, c);
        cout << A.tree[0] << '\n';
    }

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
