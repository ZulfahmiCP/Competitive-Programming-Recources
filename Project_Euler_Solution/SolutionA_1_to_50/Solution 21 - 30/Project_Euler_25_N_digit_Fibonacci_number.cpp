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

struct BigInt {
    string num;
    int digit;

    BigInt(const string& num) : num(num), digit(num.size()) {}
    BigInt(const int& a) : num(to_string(a)), digit(num.size()) {}

    int sumOfDigit() {
        int sum = 0;
        for(char &d : num)
            sum += (d - '0');
        return sum;
    }

    BigInt operator+(const BigInt& other) const {
        string sum;

        for(int i = digit - 1, j = other.digit - 1, carry = 0, digitSum; 
            i >= 0 || j >= 0 || carry; i--, j--){

            digitSum = carry;

            if(i >= 0)
                digitSum += (num[i] - '0');
            if(j >= 0)
                digitSum += (other.num[j] - '0');
            
            sum += (digitSum % 10) + '0';
            carry = digitSum / 10;
        }

        reverse(all(sum));
        return BigInt(sum);
    }

    BigInt operator-(const BigInt& other) const {
        string diff;
        int borrow = 0;

        for(int i = digit - 1, j = other.digit - 1, digitDiff;
            i >= 0 || j >= 0; i--, j--){
            
            digitDiff = num[i] - '0' - borrow;

            if(j >= 0)
                digitDiff -= (other.num[j] - '0');

            borrow = (digitDiff < 0);
            if(digitDiff < 0)
                digitDiff += 10;

            diff += (digitDiff + '0');
        }

        if(borrow)
            diff += '9';

        while(diff.back() == '0')
            diff.pop_back();

        reverse(all(diff));
        return BigInt(diff);
    }

    BigInt operator*(const BigInt& other) const {
        string product;
        int carry = 0, n = digit, m = other.digit;

        for(int i = 0, digitSum; i < n + m; i++){
            digitSum = carry;
            
            for(int j = max(0, i - m + 1); j <= min(i, n - 1); j++)
                digitSum += (num[n - j - 1] - '0') * (other.num[m - (i - j) - 1] - '0');
            
            product += ((digitSum % 10) + '0');
            carry = digitSum / 10;
        }

        if(carry)
            product += (carry + '0');
        
        while(product.back() == '0')
            product.pop_back();
        
        reverse(all(product));
        return BigInt(product);
    }

    BigInt& operator+=(const BigInt& other) {
        return *this = *this + other;
    }

    BigInt& operator+=(const int& other) {
        return *this = *this + BigInt(to_string(other));
    }

    BigInt& operator-=(const BigInt& other) {
        return *this = *this - other;
    }

    BigInt& operator-=(const int& other) {
        return *this = *this - BigInt(to_string(other));
    }

    BigInt& operator*=(const BigInt& other) {
        return *this = *this * other;
    }

    BigInt& operator*=(const int& other) {
        return *this = *this * BigInt(to_string(other));
    }

    bool operator==(const BigInt &other) const {
        return num == other.num;
    }

    bool operator!=(const BigInt &other) const {
        return num != other.num;
    }

    bool operator>=(const BigInt &other) const {
        if(digit == other.digit)
            return num >= other.num;
        return digit > other.digit;
    }

    bool operator<=(const BigInt &other) const {
        if(digit == other.digit)
            return num <= other.num;
        return digit < other.digit;
    }

    bool operator>(const BigInt& other) const {
        if(digit == other.digit)
            return num > other.num;
        return digit > other.digit;
    }

    bool operator<(const BigInt& other) const {
        if(digit == other.digit)
            return num < other.num;
        return digit < other.digit;
    }

};


int main(){
 
    FastIO();
    int t,n,mx(5e3); cin >> t;
    vector<int> Fib(mx + 1, 2e9);
    BigInt a(1), b(2), temp(0);    

    Fib[1] = 1;
    for(int i = 3; b.digit <= mx ;i++){
        Fib[b.digit] = min(Fib[b.digit], i);
        temp = b;
        b += a;
        a = temp;
    }

    for(int i = mx - 1; i > 0; i--) 
        Fib[i] = min(Fib[i], Fib[i + 1]);
        
    while(t--){
        cin >> n;
        cout << Fib[n] << '\n';
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
