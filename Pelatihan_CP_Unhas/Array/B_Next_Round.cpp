#include <bits/stdc++.h>
using namespace std;

int main() {

    int n, k; cin >> n >> k;
    vector<int> A(n);

    for(int i = 0; i < n; i++)
        cin >> A[i];

    int ans = 0;
    k--;

    for(int i = 0; i < n; i++)
        if(A[i] >= A[k] && A[i] > 0)
            ans++;
    
    cout << ans << '\n';

    return 0;
}