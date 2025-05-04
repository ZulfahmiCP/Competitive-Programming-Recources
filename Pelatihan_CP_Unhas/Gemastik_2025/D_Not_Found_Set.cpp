#include <bits/stdc++.h>
using namespace std;

int main() {

    string s; cin >> s;
    set<char> st;

    for(char &c : s)
        st.insert(c);

    for(char c = 'a'; c <= 'z'; c++){
        if(st.find(c) == st.end()){
            cout << c << '\n';
            return 0;
        }
    }

    cout << "None\n";

    return 0;
}