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

int main(){
 
    FastIO();
    int t,n,curP,curQ; cin >> t;

    auto ans = [&]() -> void {
        cin >> n;
        vector<pair<int, int>> A(n);
        vector<int> P(n), Q(n);
        vector<bool> usedP(n + 1, 0), usedQ(n + 1, 0);

        for(int i = 0; i < n; i++){
            cin >> A[i].X;
            A[i].Y = i;
        }   

        sort(all(A));

        curP = curQ = 1;
        for(int i = 0; i < n; i++){
            if(!usedP[A[i].X]){
                P[A[i].Y] = A[i].X;
                Q[A[i].Y] = curQ;

                usedP[A[i].X] = usedQ[curQ] = 1;
            } else if(!usedQ[A[i].X]){
                Q[A[i].Y] = A[i].X;
                P[A[i].Y] = curP;

                usedQ[A[i].X] = usedP[curP] = 1;
            } else {
                cout << "NO\n";
                return;
            }

            while(curP < n && usedP[curP])
                curP++;
            while(curQ < n && usedQ[curQ])
                curQ++;
        }

        if(!*min_element(1 + all(usedP)) || !*min_element(1 + all(usedQ))){
            cout << "NO\n";
            return;
        }

        for(int i = 0; i < n; i++)
            if(max(P[A[i].Y], Q[A[i].Y]) != A[i].X){
                cout << "NO\n";
                return;
            }

        cout << "YES\n";
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < n; j++)
                cout << (!i ? P[j] : Q[j]) << " \n"[j == n - 1];
    };

    while(t--)
        ans();

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
