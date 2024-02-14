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
#define X first 
#define Y second 
#define Int int64_t
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define ull unsigned long long int
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
 
void FastIO();
void FreeOpen();

const int MOD = 1e9 + 7;

struct Matrix {
    int N, M;
    vector<vector<int>> Mat;

    Matrix(const vector<vector<int>>& mat) {
        Mat = mat;
        N = Mat.size();
        M = Mat[0].size();
    }

    Matrix(int n, int m) {
        N = n, M = m;
        Mat = vector<vector<int>>(N, vector<int>(M, 0));
    }

    Matrix operator*(const Matrix& other) {
        Matrix product(N, other.M);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < other.M; j++)
                for(int k = 0; k < M; k++){
                    product.Mat[i][j] += (1LL * Mat[i][k] * other.Mat[k][j]) % MOD;
                    if(product.Mat[i][j] > MOD)
                        product.Mat[i][j] -= MOD;
                }
        debug(product.Mat);cerr << '\n';
        return product;
    }

    Matrix& operator*=(const Matrix& other) {
        return *this = *this * other;
    }
};

Matrix MatPow(Matrix A, ll B) {
    Matrix C(A.N, A.M);
    
    for(int i = 0; i < A.N; i++)
        C.Mat[i][i] = 1;

    for(; B > 0; A *= A, B >>= 1)
        if(B & 1)
            C *= A;

    return C;
}

Matrix getF(Matrix A, Matrix B) {
    return A * B;
}

int main(){
 
    FastIO();
    ll n; cin >> n;
    Matrix I({{1, 1}, {1, 0}});
    cout << (!n ? 0 : MatPow(I, n).Mat[1][0]) << '\n';

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
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); }
