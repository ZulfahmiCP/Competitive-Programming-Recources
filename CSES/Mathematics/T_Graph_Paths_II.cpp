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
const ll INFL = 4e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Matrix {
    int N, M;
    vector<vector<ll>> Mat;

    Matrix(const vector<vector<int>>& mat) : N(sz(mat)), M(sz(mat[0])) {
        Mat.resize(N, vector<ll>(M));
        for(int i = 0; i < N; i++)  
            for(int j = 0; j < M; j++)
                Mat[i][j] = mat[i][j];
    }

    Matrix(int n, int m, ll x = 0) : N(n), M(m), Mat(N, vector<ll>(M, x)) {}

    Matrix& operator*=(const Matrix& A) {
        Matrix product(N, A.M, INFL);
        assert(M == A.N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < A.M; j++)
                for(int k = 0; k < M; k++)
                    product[i][j] = min(product[i][j], Mat[i][k] + A.Mat[k][j]);
        return *this = product;
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) { return Matrix(a) *= b; }

    friend Matrix power(Matrix A, ll B) {
        if(B == 1) 
            return A;
            
        Matrix C = power(A, B >> 1);
        C = C * C;
        if(B & 1) 
            C *= A;
        return C;
    }

    vector<ll>& operator[](int i) {
        return Mat[i];
    }
};

int main(){
 
    FastIO();
    int n,m,k; cin >> n >> m >> k;
    Matrix A(n, n, INFL);

    for(int i = 0, u, v, w; i < m; i++){
        cin >> u >> v >> w, u--, v--;
        A[u][v] = min(A[u][v], (ll)w);
    }

    auto ans = power(A, k)[0][n - 1];
    cout << (ans == INFL ? -1 : ans) << '\n';

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
