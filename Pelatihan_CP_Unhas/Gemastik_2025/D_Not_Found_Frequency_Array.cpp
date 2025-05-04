#include <bits/stdc++.h>
using namespace std;

int main() {

    string s; cin >> s;
    vector<int> cnt(26, 0);

    for(char &c : s)
        cnt[c - 'a']++;

    for(char c = 'a'; c <= 'z'; c++){
        if(cnt[c] == 0){
            cout << c << '\n';
            return 0;
        }
    }

    cout << "None\n";

    return 0;
}