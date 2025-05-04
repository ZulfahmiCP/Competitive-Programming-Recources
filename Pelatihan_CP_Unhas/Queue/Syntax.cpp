#include <bits/stdc++.h>
using namespace std;

int main() {

    stack<int> st;
    st.push(1);     // st = {1}
    st.push(2);     // st = {1, 2}
    st.top();       // 2
    st.pop();       // st = {1}
    st.size();      // 1
    st.empty();     // false

    queue<int> q;
    q.push(1);      // q = {1}
    q.push(2);      // q = {1, 2}
    q.front();      // 1
    q.pop();        // q = {2}
    q.size();       // 1
    q.empty();      // false

    deque<int> dq;
    dq.push_back(0);    // dq = {0}
    dq.push_back(1);    // dq = {0, 1}
    dq.push_front(2);   // dq = {2, 0, 1}
    dq.back();          // 1
    dq.front();         // 2
    dq.pop_back();      // dq = {2, 0}
    dq.pop_front();     // dq = {0}
    dq.size();          // dq = 1
    dq.empty();         // false

    priority_queue<int> pq;
    pq.push(10);        // pq = {10, 1}
    pq.push(1);         // pq = {10, 1}
    pq.push(5);         // pq = {10, 5, 1}
    pq.top();           // 10
    pq.pop();           // pq = {5, 1}
    pq.size();          // 2
    pq.empty();         // false

    return 0;
}