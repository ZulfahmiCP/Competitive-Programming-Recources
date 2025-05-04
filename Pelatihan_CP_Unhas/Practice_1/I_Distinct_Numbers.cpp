#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    vector<int> A(n);
    
    for(int i = 0; i < n; i++) 
        cin >> A[i];

    sort(A.begin(), A.end());

    int ans = 1;

    for(int i = 1; i < n; i++)
        if(A[i] != A[i - 1])
            ans++;
    
    cout << ans << '\n';

    return 0;
}