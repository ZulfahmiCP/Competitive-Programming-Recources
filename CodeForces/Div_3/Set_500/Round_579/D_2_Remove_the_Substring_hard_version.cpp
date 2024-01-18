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
template <typename T, typename... Asub_poss>
    void printDebug(const T& value, Asub_poss... asub_poss);
template <typename... Asub_poss>
    void Debug(Asub_poss... asub_poss);
template <typename K, typename V>
    void Debug(const map<K, V>& container);
template <typename T>
    void Debug(const set<T>& container);
template <typename T>
    void Debug(const vector<T>& container);
 
void FastIO();
void FreeOpen();
void UsacoOpen();
int main(){
 
    FastIO();
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size(), ans, pos;
	vector<int> sub_pos(m);
	
	for (int i = m - 1, pos; i >= 0; --i) {
        pos = (i + 1 < m ? sub_pos[i + 1] : n) - 1;

		while(s[pos] != t[i]) 
            pos--;

		sub_pos[i] = pos;
	}

	ans = pos = 0;
	for (int i = 0, rpos; i < n; ++i) {
        rpos = (pos < m ? sub_pos[pos] : n) - 1;

		ans = max(ans, rpos - i + 1);

		if(pos < m && t[pos] == s[i]) 
            pos++;
	}
	
	cout << ans << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Asub_poss>void printDebug(const T& value, Asub_poss... asub_poss){printDebug(value); cout << ", "; printDebug(asub_poss...); }
template <typename... Asub_poss> void Debug(Asub_poss... asub_poss){ cout << "[";  printDebug(asub_poss...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
