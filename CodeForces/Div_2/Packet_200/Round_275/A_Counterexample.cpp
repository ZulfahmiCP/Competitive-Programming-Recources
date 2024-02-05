#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
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
    long long l,r; cin >> l >> r;

    if(r - l < 2 || (l & 1 && r - l == 2))   
        cout << "-1\n";
    else if(l & 1)  
        cout << l + 1 << ' ' << l + 2 << ' ' << l + 3 << '\n';
    else 
        cout << l << ' ' << l + 1 << ' ' << l + 2 << '\n';

    return 0;
}
void FastIO(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}