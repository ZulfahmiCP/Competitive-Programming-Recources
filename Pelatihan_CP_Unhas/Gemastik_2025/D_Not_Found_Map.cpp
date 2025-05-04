#include <bits/stdc++.h>
using namespace std;

int main() {

    string s; cin >> s;
    map<char, int> cnt;

    for(char &c : s)
        cnt[c]++;

    for(char c = 'a'; c <= 'z'; c++){
        if(cnt[c] == 0){
            cout << c << '\n';
            return 0;
        }
    }

    cout << "None\n";

    return 0;
}