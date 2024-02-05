#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <map>
#define ll long long
using namespace std;
 
void FastIO();
int main(){
    
    FastIO();
    int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
 
    if(x1 == x2)
        cout << x1 + abs(y1 - y2) << ' ' << y1 << ' ' << x2 + abs(y1 - y2) << ' ' << y2 << '\n';
    else if(y1 == y2)
        cout << x1 << ' ' << y1 + abs(x1 - x2) << ' ' << x2 << ' ' << y2 + abs(x1 - x2) << '\n';
    else if(abs(x1 - x2) == abs(y1 - y2))
        cout << x1 << ' ' << y2 << ' ' << x2 << ' ' << y1 << '\n';
    else 
        cout << "-1\n";
 
    return 0;
}
void FastIO(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}