#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    vector<bool> exist(n + 1, false);

    for(int i = 0; i < n - 1; i++){
        int x; cin >> x;
        exist[x] = true;
    }

    for(int i = 1; i <= n; i++){
        if(!exist[i]){
            cout << i << '\n';
            return 0;
        }
    }

    return 0;
}