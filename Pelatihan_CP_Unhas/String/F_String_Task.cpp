#include <bits/stdc++.h>
using namespace std;

bool vokal(char c) {
    return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'y';
}

int main() {

    string s; cin >> s;
    int n = s.size();

    for(int i = 0; i < n; i++){
        if(s[i] < 'a')
            s[i] += 32;
        if(!vokal(s[i]))
            cout << '.' << s[i];
    }   

    return 0;
}