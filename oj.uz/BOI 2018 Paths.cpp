#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (300005)
ll N,M,K;
vector<ll> v[MAXN];
ll colour[MAXN], memo[MAXN][(1ll<<5) + 1];
ll dp(ll x,ll bitmask){
	if(memo[x][bitmask] != -1) return memo[x][bitmask];
	ll sum = 0;
	if(__builtin_popcountll(bitmask) >= 2) sum = 1; //the problem statement defines that a path must consist of at least 2 nodes
	for(auto u : v[x]){
		if((bitmask & (1ll<<colour[u])) == 0){
			sum += dp(u,bitmask | (1ll<<colour[u]));
		}
	}
	memo[x][bitmask] = sum;
	return memo[x][bitmask];
}
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>M>>K;
	for(ll i = 0;i < N;i++){
		cin>>colour[i];
		colour[i]--;
	}
	for(ll i = 0;i < M;i++){
		ll a,b;
		cin>>a>>b;
		a--, b--;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	memset(memo,-1,sizeof(memo));
	ll ans = 0;
	for(ll x = 0;x < N;x++){
		ans += dp(x,1ll<<colour[x]);
	}
	cout<<ans<<'\n';
}
