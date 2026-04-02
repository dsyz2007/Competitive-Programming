#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (2005)
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,L,T;
	cin>>N>>L>>T;
	deque<ll> A;
	for(ll i = 0;i < N;i++){
		ll a;
		cin>>a;
		A.push_back(a);
	}
	A.push_front(0);
	while(!A.empty() && A.back() > L){
		A.pop_back();
	}
	A.push_back(L); //remember to ans -= 2 (pos 0 and pos L)
	N = A.size();
	ll dp[N][N + 1];
	for(ll i = 0;i < N;i++){
		for(ll j = 0;j <= N;j++){
			dp[i][j] = 1e18;
		}
	}
	deque<ll> prev[N + 1];
	multiset<ll> best1[N + 1];
	ll best2[N + 1];
	for(ll j = 0;j <= N + 1;j++){
		best2[j] = 1e18;
	}
	dp[0][1] = 1; //start with height 1 (remember to minus 1 to ans)
	prev[1].push_back(0); //index
	best1[1].insert(dp[0][1]); //value
	for(ll i = 1;i < N;i++){
		for(ll j = i;j >= 1;j--){
			best2[j] += (A[i] - A[i - 1]);
			while(!prev[j].empty() && A[i] - A[prev[j].front()] >= dp[prev[j].front()][j]){
				best1[j].erase(best1[j].find(dp[prev[j].front()][j]));
				if(A[i] - A[prev[j].front()] < best2[j]) best2[j] = A[i] - A[prev[j].front()];
				prev[j].pop_front();
			}
		}
		for(ll j = i + 1;j >= 2;j--){
			if(!best1[j - 1].empty()) dp[i][j] = min(dp[i][j],*best1[j - 1].begin());
			dp[i][j] = min(dp[i][j],best2[j - 1]);
			prev[j].push_back(i);
			best1[j].insert(dp[i][j]);
		}
	}
	ll minimum = 1e18;
	for(ll j = 2;j <= N;j++){
		minimum = min(minimum,(dp[N - 1][j] - 1) + (j - 2) * T);
	}
	cout<<minimum<<'\n';
}
