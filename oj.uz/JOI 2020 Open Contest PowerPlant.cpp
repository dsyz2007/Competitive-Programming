#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (200005)
vector<ll> v[MAXN];
bool generator[MAXN];
ll dp[MAXN];
ll ans = 0;
void dfs(ll x,ll p){
    ll maximum = 0;
    ll sum = 0;
    for(auto u : v[x]){
        if(u != p){
            dfs(u,x);
            maximum = max(maximum,dp[u]);
            sum += dp[u];
        }
    }
    if(generator[x]){
		dp[x] = max(1ll,sum - generator[x]);
	}else{
		dp[x] = sum - generator[x];
	}
    ans = max(ans,dp[x]);
    ans = max(ans,maximum + generator[x]);
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N;
	cin>>N;
	for(ll i = 0;i < N - 1;i++){
	    ll a,b;
	    cin>>a>>b;
	    a--;
	    b--;
	    v[a].push_back(b);
	    v[b].push_back(a);
	}
	string s;
	cin>>s;
	for(ll i = 0;i < N;i++){
	    if(s[i] == '0') generator[i] = 0;
	    else generator[i] = 1;
	}
	dfs(0,-1);
	cout<<ans<<'\n';
}
