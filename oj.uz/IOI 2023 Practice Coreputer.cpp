#include <bits/stdc++.h>
#include "coreputer.h"
using namespace std;
using ll = long long;
#define MAXN (1000005)
 
vector<int> malfunctioning_cores(int N) {
	ll high = N - 1;
	ll low = -1;
  	ll parity = 1; //parity of total number of malfunctioning cores
	while(high - low > 1){ //binary search for leftmost position such that prefix sum of malfunctioning cores > half of total malfunctioning cores
		ll mid = (high + low) / 2;
		vector<int> T;
		for(ll i = 0;i <= mid;i++){
			T.push_back(i);
		}
		ll a = run_diagnostic(T);
		if(a == 1){
			high = mid;
		}else{
          	if(a == 0) parity = 0;
			low = mid;
		}
	}
	ll checked = 1;
	vector<ll> malfunctioning;
	malfunctioning.push_back(high);
	for(ll i = 0;i < high;i++){
		if(checked == 15){
			if((ll(malfunctioning.size()) % 2) == parity){
				checked++;
			}else{
				checked++;
				malfunctioning.push_back(i);
			}
			break;
		}
		vector<int> T;
		for(ll j = 0;j <= high;j++){
			if(i == j) continue;
			T.push_back(j);
		}
		ll a = run_diagnostic(T);
		if(a == 0){
			malfunctioning.push_back(i);
		}else if(a == -1){
			malfunctioning.push_back(i);
		}
		checked++;
	}
	for(ll i = high + 1;i < N && ll(malfunctioning.size()) >= 2;i++){
		if(checked == 15){
			if((ll(malfunctioning.size()) % 2) == parity){
				checked++;
			}else{
				checked++;
				malfunctioning.push_back(i);
			}
			break;
		}
		vector<int> T;
		for(ll j = high;j < N;j++){
			if(i == j) continue;
			T.push_back(j);
		}
		ll a = run_diagnostic(T);
		if(a == -1){
			malfunctioning.push_back(i);
		}
		checked++;
	}
	vector<int> ans;
	for(ll i = 0;i < N;i++){
		ans.push_back(0);
	}
	for(auto u : malfunctioning){
		ans[u] = 1;
	}
	return ans;
}
