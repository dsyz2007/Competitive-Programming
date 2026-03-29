#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,M;
	cin>>N>>M;
	ll A[N];
	ll maxA = 0;
	for(ll i = 0;i < N;i++){
		cin>>A[i];
		maxA = max(maxA,A[i]);
	}
	vector<ll> v[N];
	for(ll i = 0;i < M;i++){
		ll a,b;
		cin>>a>>b;
		a--;
		b--;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > pq;
	ll start[N]; //either 0 or N - 1
	ll dist[N];
	memset(start,-1,sizeof(start));
	memset(dist,-1,sizeof(dist));
	dist[0] = 0;
	dist[N - 1] = 0;
	start[0] = 0;
	start[N - 1] = N - 1;
	pq.push({dist[0],0});
	pq.push({dist[N - 1],N - 1});
	while(!pq.empty()){
		ll x = pq.top().second;
		ll d = pq.top().first;
		pq.pop();
		if(d != dist[x]){
			continue;
		}
		for(auto u : v[x]){
			if(dist[u] == -1 || dist[u] > max(A[u],dist[x] + 1)){
				dist[u] = max(A[u],dist[x] + 1);
				start[u] = start[x]; //started from node 0 or N - 1
				pq.push({dist[u],u});
			}
		}
	}
	ll ans = 1e18;
	for(ll x = 0;x < N;x++){
		for(auto u : v[x]){
			if(start[x] != start[u]){ 
				//one started from node 0, another one from node N - 1
				ll a = x;
				ll b = u;
				if(dist[a] > dist[b]) swap(a,b); //dist[a] is smaller
				ans = min(ans,dist[b] + max(A[b],dist[a] + 1));
			}
		}
	}
	cout<<ans<<'\n';
}
