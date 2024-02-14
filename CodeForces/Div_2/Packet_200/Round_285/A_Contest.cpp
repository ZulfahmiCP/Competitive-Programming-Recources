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
    int a,b,c,d; cin >> a >> b >> c >> d;

    a = max(3*a/10, a - a*c/250), b = max(3*b/10, b - b*d/250);

    if(a > b)
        cout << "Misha\n";
    else if(a < b)
        cout << "Vasya\n";
    else 
        cout << "Tie\n";

    return 0;
}
void FastIO(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}