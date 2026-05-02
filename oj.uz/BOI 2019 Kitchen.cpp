#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (305)
ll N,M,K,totalA;
ll A[MAXN], B[MAXN];
ll dp[MAXN * MAXN];
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>M>>K;
	bool ok = 1;
	for(ll i = 0;i < N;i++){ //number of dishes
		cin>>A[i];
		totalA += A[i];
		if(A[i] < K) ok = 0;
	}
	for(ll i = 0;i < M;i++){ //number of chefs
		cin>>B[i];
	}
	if(!ok){
		cout<<"Impossible"<<'\n';
		return 0;
	}
	for(ll i = 0;i < MAXN * MAXN;i++){
		dp[i] = -1e18;
	}
	dp[0] = 0;
	for(ll i = 0;i < M;i++){
		for(ll j = MAXN * MAXN - 1;j >= B[i];j--){
			dp[j] = max(dp[j],dp[j - B[i]] + min(B[i],N));
		}
	}
	ll minimum = 1e18;
	for(ll i = totalA;i < MAXN * MAXN;i++){
		if(dp[i] >= N * K){
			minimum = i;
			break;
		}
	}
	if(minimum == 1e18) cout<<"Impossible"<<'\n';
	else cout<<minimum - totalA<<'\n';
}
