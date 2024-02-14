#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <map>
using namespace std;

void FastIO();
int main(){
    
    FastIO();
    int n,a; cin >> n;
	multiset<int> elem;
	for (int i = 0; i < n; ++i) {
		cin >> a;
		elem.insert(a);
	}
	
	int x = *prev(elem.end());
	for (int i = 1; i < x + 1; i++) 
		if (!(x % i)) 
			elem.erase(elem.find(i));
		
	
	
	cout << x << " " << *prev(elem.end()) << '\n';

    return 0;
}
void FastIO(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}