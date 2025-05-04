#include <bits/stdc++.h>
using namespace std;

string lower(string &s) {
    for(int i = 0; i < s.size(); i++)
        if('A' <= s[i] && s[i] <= 'Z')
            s[i] += 32;
    return s;
}

int main() {

    string s; cin >> s;
    string t; cin >> t;

    bool diff = false;

    if(s == t)
        cout << "same";
    else if(lower(s) == lower(t))
        cout << "case-insensitive";
    else 
        cout << "different";

    return 0;
}