#include <bits/stdc++.h>
using namespace std;

int main() {

    int N,Q; cin >> N >> Q;
    deque<int> ayam;

    bool reverse = true;

    for(int i = 0; i < N; i++){
        int x; cin >> x;
        ayam.push_back(x);
    }

    for(int i = 0; i < Q; i++){
        string op; cin >> op;

        if(op == "reverse"){
            reverse = !reverse;
            continue;
        }

        bool belakang = false;

        if(op == "back" && !reverse)
            belakang = true;
        if(op == "front" && reverse)    
            belakang = true;

        if(belakang){
            cout << ayam.back() << '\n';
            ayam.pop_back();
        } else {
            cout << ayam.front() << '\n';
            ayam.pop_front();
        }
    }

    return 0;
}