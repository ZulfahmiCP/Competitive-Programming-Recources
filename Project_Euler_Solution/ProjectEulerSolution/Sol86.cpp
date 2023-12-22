#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <map>
#define ll long long int
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
    int mx = 5e7, a = sqrt(mx), b = cbrt(mx), c = sqrt(sqrt(mx));
    vector<bool> prime(a + 1, 1);
    vector<vector<int>> primes(3);

    for(int i = 2; i*i <= a; i++)
        if(prime[i]){
            if(i <= a)
                primes[0].push_back(i);
            if(i <= b)
                primes[1].push_back(i);
            if(i <= c)
                primes[2].push_back(i);
            
            for(int j = i*i; j <= a; j += i)
                prime[j] = 0;
        }
    for(int i = sqrt(a) + 1; i <= a; i++)
        if(prime[i]){
            if(i <= a)
                primes[0].push_back(i);
            if(i <= b)
                primes[1].push_back(i);
            if(i <= c)
                primes[2].push_back(i);
        }
    
    vector<map<int, int>> powerI(3);

    for(int p : primes[0])
        powerI[0][p] = p*p;
    for(int p : primes[1])
        powerI[1][p] = p*p*p;
    for(int p : primes[2])
        powerI[2][p] = p*p*p*p;

    set<int> prime_power_triple;
    for(int p : primes[0])
        for(int q : primes[1])
            for(int r : primes[2]){
                int N = powerI[0][p] + powerI[1][q] + powerI[2][r];
                if(N < mx)
                    prime_power_triple.insert(N);
            }
    Debug(prime_power_triple.size());

    return 0;
}

void FastIO(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
void FreeOpen(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}
template <typename T>
void printDebug(const T& x){
    cout << x;
}
template <typename T, typename U>
void printDebug(const pair<T, U>& value){
    cout << "("; printDebug(value.first); 
    cout << ", "; printDebug(value.second); cout << ")";
}
template <typename T, typename... Args>
void printDebug(const T& value, Args... args){
    cout << value << ", ";
    printDebug(args...);
}
template <typename... Args>
void Debug(Args... args){
    cout << "[";
    printDebug(args...);
    cout << "]\n";
}
template <typename K, typename V>
    void Debug(const map<K, V>& container){
        cout << '[';
        bool comma = 0;
        for(auto [k, v] : container){
            if(comma) cout << ", ";
            cout << '[';
            printDebug(k); cout << ", ";
            printDebug(v); cout << ']';
            comma = 1;
        }
        cout << "]\n";
    }
template <typename T>
    void Debug(const set<T>& container) {
    cout << '[';
    bool comma = 0;
    for (const auto& item : container) {
        if (comma) cout << ", ";
        printDebug(item);
        comma = 1;
    }
    cout << "]\n";
}
template <typename T>
void Debug(const vector<T>& container) {
    cout << '[';
    bool comma = 0;
    for (const auto& item : container) {
        if (comma) cout << ", ";
        printDebug(item);
        comma = 1;
    }
    cout << "]\n";
}
