#include <bits/stdc++.h>
using namespace std;

int main() {

    int t,n; cin >> t;
    int MAX = 1e5; // 10^5

    while(t--){
        cin >> n;
        vector<int> A(n);
        vector<int> cnt(MAX + 1, 0);

        for(int i = 0; i < n; i++)
            cin >> A[i];

        bool valid = true;

        for(int i = 0; i < n; i++){
            cnt[A[i]]++;
            if(cnt[A[i]] > 1)
                valid = false;
        }

        cout << (valid ? "prekrasnyy" : "ne krasivo") << '\n';
    }

    return 0;
}