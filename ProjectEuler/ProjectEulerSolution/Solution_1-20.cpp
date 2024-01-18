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
        *this = *this + other;
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        *this = *this - other;
        return *this;
    }

    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
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
    
    auto Solution_1 = [&]() {
        /*Find the sum of all the multiples of a and b below n*/
        ll a,b,n; cin >> a >> b >> n; n--;
        Debug((n/a) + (n/b) - (n/(a*b)));
    };

    auto Solution_2 = [&]() {
        /*Find the sum of the even-valued terms that do not exceed n*/
        vector<int> Fib = {1, 2};
        ll n; cin >> n;

        ll even_valued_count = 0;
        for(int i = 2; Fib[i] <= n; i++){
            Fib[i] = Fib[i - 1] + Fib[i - 2];
            even_valued_count += (!(Fib[i] & 1));
        }

        Debug(even_valued_count);
    };

    auto Solution_3 = [&]() {
        /*What is the largest prime factor of n*/
        ll n; cin >> n;

        ll largest_prime_factor = n;
        for(int i = 2; i*i <= n; i++)
            if(!(n % i)){
                largest_prime_factor = i;
                while(!(n % i))
                    n /= i;
            }
        
        Debug(largest_prime_factor);
    };

    auto Solution_4 = [&]() {
        /*Find the largest palindrome made from the product of a and b digit number */
        ll a,b,largest_palindrome; cin >> a >> b;

        auto is_palindrome = [&](ll n) -> bool {
            string s = to_string(n);
            n = s.size();
            for(int i = 0; i < (n >> 1); i++)
                if(s[i] != s[n - i - 1])
                    return 0;
            return 1;
        };

        a = pow(10, a), b = pow(10, b);
        for(int i = a; i < 10*a; i++)
            for(int j = b; j < 10*b; j++)
                if(is_palindrome(a*b) && a*b > largest_palindrome)
                    largest_palindrome = a*b;
        Debug(largest_palindrome);
    };

    auto Solution_5 = [&]() {
        /*Find the smallest number that evenly divisible by all number for 1 to n*/
        int n; cin >> n;

        function<ll(ll, ll)> gcd = [&](ll a, ll b) -> ll {
            if(!b) return a;
            return gcd(b, a % b);
        };

        auto lcm = [&](ll a, ll b) -> ll {
            return a*b/gcd(a, b);
        };  

        ll smallest_num = 1;
        for(int i = 2; i <= n; i++)
            smallest_num = lcm(smallest_num, i);
        Debug(smallest_num);
    };

    auto Solution_6 = [&]() {
        /*Find the result of (1 + 2 + ... + n)^2 - (1^2 + 2^2 + ... + n^2)*/
        ll n; cin >> n;
        Debug((n*(n + 1)*(n*(n + 3) - 1))/2);
    };

    auto Solution_7 = [&]() {
        /*Find the n-th prime number the below 10^8*/
        int n,MAX = 1e8; cin >> n;
        vector<bool> prime(MAX + 1, 1);
        
        for(int i = 2; i*i <= MAX; i++)
            if(prime[i])
                for(int j = i*i; j <= MAX; j += i)
                    prime[j] = 0;

        int curPrime = 0;
        for(int i = 2; i <= MAX; i++){
            curPrime += prime[i];
            if(curPrime == n){
                Debug(i);
                return;
            }
        }
    };

    auto Solution_8 = [&]() {
        /*Find the maximum product of 4 adjacent number in the 1000-digit*/
        string s; 

        string digit;
        for(int i = 0; i < 20; i++){
            cin >> digit;
            s += digit;
        }

        int product = 0;
        for(int i = 0, p; i < 1e3 - 3; i++){
            p = 1;
            for(int j = i; j < i + 4; j++)
                p *= (s[j] - '0');
            product = max(product, p);
        }

        cout << product << '\n';
    };

    auto Solution_9 = [&]() {
        /*Find product of pythagorian triples that sum up to even number n*/
        int n; cin >> n;
        for(ll c = n/3 + 1; c < n/2; c++)
            for(int i = 2; i*i < c; i++)
                if(!(c % i)){
                    ll a = i, b = c/i;
                    if(a + b + c == n && a*a + b*b == c*c){
                        Debug(a, b, c, a*b*c);
                        return;
                    }
                }
    };

    auto Solution_10 = [&]() {
        /*Find the sum of all the primes below n*/
        int n; cin >> n;
        ll sum_of_primes = 0;
        vector<bool> prime(n + 1, 1);

        for(ll i = 2; i*i <= n; i++)
            if(prime[i]){
                sum_of_primes += i;
                for(int j = i*i; j <= n; j += i)
                    prime[j] = 0;
            }
        
        Debug(sum_of_primes);
    };

    auto Solution_11 = [&]() {
        /*Find the greatest product of k adjacent number in the same direction
          (up, down, right, left) in n x n grid*/
        int n,k; cin >> n >> k;
        vector<vector<ll>> grid(n, vector<ll>(20));

        ll largest_product = 1;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> grid[i][j];
        
        for(int i = 0; i < n; i++)
            for(ll j = 0, pRow, pCol; j <= n - k; j++){
                pCol = pRow = 1;
                for(int l = j; l < j + k; l++){
                    pCol *= grid[j][l];
                    pRow *= grid[l][j];
                }

                largest_product = max(largest_product, max(pCol, pRow));
            }
    
        for(int i = 0; i <= n - k; i++)
            for(ll j = 0, pDiag; j <= n - k; j++){
                pDiag = 1;
                for(int l = j; l < j + k; l++)
                    pDiag *= grid[l][l];
                
                largest_product = max(largest_product, pDiag);
            }

        for(int i = 0; i < n - 3; i++)
            for(ll j = 4, pDiag; j < n; j++){
                pDiag = 1;
                for(int l = 0; l < k; l++)
                    pDiag *= grid[i][l];
                
                largest_product = max(largest_product, pDiag);
            }
                    
        cout << largest_product << '\n'; 
    };

    auto Solution_12 = [&]() {
        /*Find the value of the first triangle number (Tn = n*(n + 1)/2)
          to have over n divisors*/ 
        ll n; cin >> n;

        for(ll i = 1, x,d = 0;; i++){
            x = i*(i + 1) >> 1, d = 0;
            for(int j = 1; j*j <= x; j++){
                if(j*j == x)
                    d++;
                else if(!(x % j))
                    d += 2;
            }

            if(d >= n){
                Debug(i, x, d, n);
                return;
            }
        }
    };

    auto Solution_13 = [&]() {
        /*Work out the first ten digits of the sum 
          of the following one-hundred 50-digit numbers.*/
        auto add_string = [&](string a, string b) -> string {
             if(a.size() < b.size())
                swap(a, b);
            while(b.size() != a.size())
                b = "0" + b;
        
            int n = a.size(), carry = 0;
            string result;
            for(int i = n - 1; i > -1; i--){
                int digit = (a[i] - '0' + b[i] - '0');
                result = (char)(((digit % 10) + carry) % 10 + '0') + result;
                carry = (digit + carry)/10;
            }

            if(carry)
                result = to_string(carry) + result;

            return result;
        };

        vector<string> digit_list(50);

        for(int i = 0; i < 50; i++)
            cin >> digit_list[i];
        
        string answer = digit_list[0];
        for(int i = 1; i < 50; i++)
            answer = add_string(answer, digit_list[1]);
        
        Debug(answer.substr(0, 10));
    };

    auto Solution_14 = [&]() {
        /*The collatz sequence is defined as a set of this integer
          n -> n/2(n even) and n -> 3n + 1(n odd). Which staring number
          that under mx that produces longest chain*/
        ll mx; cin >> mx;
        ll longest_chain = 0, starting_number_longest_chain;
        vector<bool> visited(mx, 0);
        vector<ll> sequence(mx);

        function<ll(ll)> collatz = [&](ll n) -> ll {
            if(n > mx){
                ll chain = (n & 1 ? collatz(3*n + 1) : collatz(n/2)) + 1;
                return chain;
            }

            if(visited[n])
                return sequence[n];
            visited[n] = 1;

            sequence[n] = (n & 1 ? collatz(3*n + 1) : collatz(n/2)) + 1;
            return sequence[n];
        };

        visited[1] = 1; sequence[1] = 1;
        for(ll i = 2; i < mx; i++)
            if(!visited[i] && collatz(i) > longest_chain)
                longest_chain = sequence[i], starting_number_longest_chain = i;
        Debug(starting_number_longest_chain, longest_chain);
    };

    auto Solution_15 = [&]() {
        int n; cin >> n; n++;
        vector<vector<ll>> path(n, vector<ll>(n));

        for(int i = 0; i < n; i++)
            path[n - 1][i] = path[i][n - 1] = 1;
        for(int i = n - 2; i > -1; i--)
            for(int j = n - 2; j > -1; j--)
                path[i][j] = path[i + 1][j] + path[i][j + 1];
    
        Debug(path[0][0]);
    };

    auto Solution_16 = [&]() {
        /*Find the sum of digit of the number n*/
        int n, MX = 5e6, curDigit = 1; cin >> n;
        vector<int> digit(MX);

        digit[0] = 1;
        for(int i = 0, sum; i < 1000; i++){
            sum = 0;
            for(int j = 0, c; j < curDigit; j++){
                c = 2*digit[j];
                digit[j] = c % 10 + sum % 10;

                sum /= 10;
                sum += (c/10);
            }

            while(sum){
                digit[curDigit] = sum % 10;
                sum /= 10;
                curDigit++;
            }
        }

        int digit_sum = 0;
        for(int i = 0; i < curDigit; i++)
            digit_sum += digit[i];
        Debug(digit_sum);

        /*Alternative Solution*/

        auto multiple_two = [&](string a) -> string {
            int n = a.size(), carry = 0;
            string result;
            for(int i = n - 1; i > -1; i--){
                int digit = 2*(a[i] - '0');
                result = (char)(((digit % 10) + carry % 10) % 10 + '0') + result;
                carry = (digit + carry)/10;
            }

            if(carry)
                result = to_string(carry) + result;

            return result;
        };

        int N, digitSum = 0; cin >> N;
        string result = "1";
        for(int i = 0; i < N; i++)
            result = multiple_two(result);
        for(int i = 0; i < result.size(); i++)
            digitSum += (result[i] - '0');
        Debug(digitSum);
    };

    auto Solution_17 = [&]() {
        /*If all the numbers from 1 to 1000 inclusive were 
          written out in words, how many letters would be used?*/
        vector<string> number = {"zero", "one", "two", "three", "four", "five", 
        "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", 
        "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
        vector<string> tens = {"", "", "twenty", "thirty", "forty", "fifty", 
        "sixty", "seventy", "eighty", "ninety"};

        function<int(int)> number_letter_count = [&](int n) -> int {
            if(n < 20)
                return number[n].size();
            else if(n < 100)
                return (number[n/10].size() + number[n % 10].size());
            else if(n < 1000)
                return (number[n/100].size() + 7 + 
                        (n % 100 ? 3 + number_letter_count(n % 100) : 0));
            else if(n == 1000)
                return 11;
            return 0;
        };

        int num_letter_sum = 0;
        for(int i = 1; i <= 1000; i++)
            num_letter_sum += (number_letter_count(i));
        Debug(num_letter_sum);
    };

    auto Solution_18 = [&]() {
        /*Find the maximum total from top to bottom of
          the number in a form of a triangle of depth n*/
        int n; cin >> n;
        vector<vector<ll>> triangle(n);

        for(int i = 0; i < n; i++)
            for(ll j = 0, a; j <= i; j++){
                cin >> a;
                triangle[i].push_back(a);
            }
        
        for(int i = n - 2; i > -1; i--)
            for(int j = 0; j <= i; j++)
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
        Debug(triangle[0][0]);
    };

    auto Solution_19 = [&]() {
        int count = 0, dayOfWeek = 1;  

        for (int year = 1901; year <= 2000; ++year) {
            for (int month = 1; month <= 12; ++month) {
                count += (!dayOfWeek); 

                int daysInMonth;
                if(month == 4 || month == 6 || month == 9 || month == 11)
                    daysInMonth = 30;
                else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 10 || month == 12) 
                    daysInMonth = 31;
                else if((!(year % 4) && (year % 100)) || !(year % 400))
                    daysInMonth = 29;
                else 
                    daysInMonth = 28;

                dayOfWeek = (dayOfWeek + daysInMonth) % 7;
            }
        }

        Debug(count);
    };

    auto Solution_20 = [&]() {
        /*Find the sum of digit in the number n!*/
        int n; cin >> n;
        BigInt result("1");

        for(int i = 2; i <= n; i++)
            result *= to_string(i);
        
        cout << result.sumOfDigit() << '\n';
    };

    int number; cin >> number;
    switch(number){
        case 1 : Solution_1(); break;
        case 2 : Solution_2(); break;
        case 3 : Solution_3(); break;
        case 4 : Solution_4(); break;
        case 5 : Solution_5(); break;
        case 6 : Solution_6(); break;
        case 7 : Solution_7(); break;
        case 8 : Solution_8(); break;
        case 9 : Solution_9(); break;
        case 10: Solution_10(); break;
        case 11: Solution_11(); break;
        case 12: Solution_12(); break;
        case 13: Solution_13(); break;
        case 14: Solution_14(); break;
        case 15: Solution_15(); break;
        case 16: Solution_16(); break;
        case 17: Solution_17(); break;
        case 18: Solution_18(); break;
        case 19: Solution_19(); break;
        case 20: Solution_20(); break;
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
