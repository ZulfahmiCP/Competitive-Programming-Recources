#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <complex>
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
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;
const double PI = acos(-1.0);

void FastIO();


struct FFT {
    void fft(vector<complex<double>>& A, bool inv) {
        int N = sz(A);

        for(int i = 1, j = 0, bit; i < N; i++){
            bit = N >> 1;
            for(; j & bit; bit >>= 1) 
                j ^= bit;
            j ^= bit;

            if(i < j) 
                swap(A[i], A[j]);
        }

        for(int k = 2; k <= N; k <<= 1){
            double angle = 2 * PI / k * (inv ? -1 : 1);
            complex<double> wlen(cos(angle), sin(angle));

            for(int i = 0; i < N; i += k) {
                complex<double> w(1);
                for(int j = 0; j < k / 2; j++){
                    complex<double> u = A[i + j], v = A[i + j + k / 2] * w;
                    A[i + j] = u + v, A[i + j + k / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if(inv) for(auto &a : A) a /= N;
    }

    vector<ll> multiply(const vector<int>& A, const vector<int>& B) {
        int N = 1;
        while(N <= max(sz(A), sz(B)))
            N <<= 1;
        N <<= 1;

        vector<complex<double>> FA(all(A));
        vector<complex<double>> FB(all(B));

        FA.resize(N);
        FB.resize(N);

        fft(FA, 0);
        fft(FB, 0);
        for(int i = 0; i < N; ++i) 
            FA[i] *= FB[i];
        fft(FA, 1);

        vector<ll> ans(N);
        for(int i = 0; i < N; i++) 
            ans[i] = round(FA[i].real());

        return ans;
    }
};

int main() {

    FastIO();
    int n,m,k; cin >> k >> n >> m;
    vector<int> A(k + 1, 0), B(k + 1, 0);

    for(int i = 0, x; i < n; i++){
        cin >> x;
        A[x]++;
    }

    for(int i = 0, x; i < m; i++){
        cin >> x;
        B[x]++;
    }

    FFT fft;
    auto ans = fft.multiply(A, B);

    for(int i = 2; i <= 2 * k; i++)
        cout << ans[i] << ' ';

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
