#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    vector<int> A(n);

    for(int i = 0; i < n; i++)
        cin >> A[i];

    int ans = 1e9; // 10^9

    for(int i = 0; i < n; i++)
        ans = min(ans, abs(A[i]));

    cout << ans << '\n';

    return 0;
}