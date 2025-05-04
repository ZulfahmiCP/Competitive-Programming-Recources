#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    vector<int> A(n);

    for(int i = 0; i < n; i++)
        cin >> A[i];

    sort(A.begin(), A.end());

    cout << A[n / 2] << '\n';

    return 0;
}