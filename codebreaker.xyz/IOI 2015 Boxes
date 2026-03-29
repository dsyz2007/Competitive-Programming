#include <bits/stdc++.h>
#include "boxes.h"
using namespace std;
using ll = long long;
#define MAXN (1000005)

long long delivery(int N, int K, int L, int p[]) {
    ll minimum = 5e18;
    ll clockwise[N + 5];
    memset(clockwise,0,sizeof(clockwise));
    for(ll i = 0;i < N;i++){
		if(i < K){
			clockwise[i + 1] = 2 * p[i];
		}else{
			clockwise[i + 1] = clockwise[i + 1 - K] + (2 * p[i]);
		}
	}
	ll anticlockwise[N + 5];
	memset(anticlockwise,0,sizeof(anticlockwise));
	for(ll i = N - 1;i >= 0;i--){
		if(i >= N - K + 1){
			anticlockwise[i + 1] = 2 * (L - p[i]);
		}else{
			anticlockwise[i + 1] = anticlockwise[i + 1 + K] + (2 * (L - p[i]));
		}
	}
	for(ll i = 0;i <= N;i++){
		minimum = min(minimum,clockwise[i] + anticlockwise[i + 1]);
	}
	for(ll i = 0;i <= N - K;i++){
		minimum = min(minimum,clockwise[i] + anticlockwise[i + 1 + K] + L);
	}
	return minimum;
}
