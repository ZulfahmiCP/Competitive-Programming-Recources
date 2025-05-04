#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n; cin >> t;
    
    while(t--){
        cin >> n;
        vector<int> A(n);

        for(int i = 0; i < n; i++)
            cin >> A[i];

        for(int i = 0; i < n; i++)
            cout << n + 1 - A[i] << ' ';
        cout << '\n';
    }

    return 0;
}