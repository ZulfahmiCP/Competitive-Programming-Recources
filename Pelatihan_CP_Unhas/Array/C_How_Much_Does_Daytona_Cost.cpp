#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n, k; cin >> t;

    while(t--){
        cin >> n >> k;
        bool exist = false;

        for(int i = 0; i < n; i++){
            int x; cin >> x;
            if(x == k)
                exist = true;
        }

        cout << (exist ? "YES" : "NO") << '\n';
    }       

    return 0;
}