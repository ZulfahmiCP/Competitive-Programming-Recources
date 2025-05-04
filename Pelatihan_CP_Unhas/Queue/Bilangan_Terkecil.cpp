#include <bits/stdc++.h>
using namespace std;

int main() {

    int N; cin >> N;
    vector<int> A(N);

    for(int i = 0; i < N; i++)
        cin >> A[i];

    int answer = 0;
    int hp = 0;
    priority_queue<int, vector<int>, 
    greater<int>> pq;

    for(int i = 0; i < N; i++){
        hp += A[i];
        pq.push(A[i]);

        while(hp < 0){
            hp -= pq.top();
            pq.pop();
        }

        if(pq.size() > answer)
            answer = pq.size();
    }

    cout << answer << '\n';

    return 0;
}