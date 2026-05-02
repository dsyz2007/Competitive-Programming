#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define MAXN (300005)
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,K;
	cin>>N>>K;
	deque<pair<ll,ll> > arr;
	for(ll i = 1;i <= N;i++){
		ll a,b;
		cin>>a>>b;
		if(b == -1) b = 1e18;
		arr.push_back(make_pair(b,a));
	}
	sort(arr.begin(),arr.end());
	arr.push_front(make_pair(0,0));
	ld A[N + 1], B[N + 1]; //1-indexed
	A[0] = 0;
	B[0] = 0;
	for(ll i = 1;i <= N;i++){
		A[i] = arr[i].second;
		B[i] = arr[i].first;
	}
	ld dp[N + 5][N + 5]; //first i states considered, j of them belong in B[i] = -1
	ld ans = 1e18;
	for(ll m = 0;m <= K;m++){ //m collaborators gained in total
		for(ll i = 0;i <= N;i++){
			for(ll j = 0;j <= N;j++){
				dp[i][j] = 1e18;
			}
		}
		dp[0][0] = 0;
		for(ll i = 1;i <= N;i++){ //first i states considered
			for(ll j = 0;j <= i;j++){ //j states are non-collaborators
				ld valA = A[i] / (m + 1);
				ld valB = B[i] / min(i - j,m);
				dp[i][j] = min(dp[i][j],dp[i - 1][j] + valB);
				if(i - j > m) dp[i][j] = min(dp[i][j],dp[i - 1][j]);
				if(j >= 1) dp[i][j] = min(dp[i][j],dp[i - 1][j - 1] + valA);
			}
		}
		ans = min(ans,dp[N][K - m]);
	}
	cout<<fixed<<setprecision(10);
	cout<<ans<<'\n';
}
