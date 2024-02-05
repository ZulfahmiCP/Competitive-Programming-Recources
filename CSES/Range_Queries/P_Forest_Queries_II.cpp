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

struct Fenwick {
    int N, M;
    vector<vector<int>> mat, bit;

    Fenwick(int n, int m) : N(n), M(m) {
        mat.resize(N, vector<int>(M));
        bit.resize(N + 1, vector<int>(M + 1, 0));
    }

    void build() {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                update(i, j, mat[i][j]);
    }

    Fenwick(vector<vector<int>>& matrix) {
        mat = matrix, N = mat.size(), M = mat[0].size();
        bit.resize(N + 1, vector<int>(M + 1, 0));
        build();
    }

    void update(int x, int y, int val) {
        for(int i = x + 1; i <= N; i += (i & -i)) 
            for(int j = y + 1; j <= M; j += (j & -j)) 
                bit[i][j] += val;
    }

    int query(int x, int y) {
        int sum = 0;
        for(int i = x + 1; i > 0; i -= i & -i) 
            for(int j = y + 1; j > 0; j -= j & -j) 
                sum += bit[i][j];
        return sum;
    }

    int sum(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
    
};

int main() {

    FastIO();
    int n,q; cin >> n >> q;
    vector A(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            char c; cin >> c;
            A[i][j] = c == '*';
        }

    Fenwick fenwick(A);
    for(int i = 0, t,x,y,a,b; i < q; i++){
        cin >> t >> x >> y, x--, y--;

        if(t == 1){
            fenwick.update(x, y, A[x][y] ? -1 : 1);
            A[x][y] = !A[x][y];
        } else {
            cin >> a >> b, a--, b--;
            cout << fenwick.sum(x, y, a, b) << '\n';
        }
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
