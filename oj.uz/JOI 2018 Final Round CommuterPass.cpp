#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (100005)
ll N,M,S,T,U,V;
vector<pair<ll,ll> > v[MAXN];
ll distS[MAXN], distT[MAXN];
void dijkstra(ll start){
	ll dist[MAXN];
	memset(dist,-1,sizeof(dist));
	priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > pq;
	pq.push({0,start});
	dist[start] = 0;
	while(!pq.empty()){
		ll d = pq.top().first;
		ll x = pq.top().second;
		pq.pop();
		if(d != dist[x]){
			continue;
		}
		for(auto u : v[x]){
			if(dist[u.first] == -1 || dist[u.first] > dist[x] + u.second){
				dist[u.first] = dist[x] + u.second;
				pq.push({dist[u.first],u.first});
			}
		}
	}
	if(start == S){
		for(ll i = 0;i < N;i++){
			distS[i] = dist[i];
		}
	}else if(start == T){
		for(ll i = 0;i < N;i++){
			distT[i] = dist[i];
		}
	}else{
		assert(false);
	}
}
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>M>>S>>T>>U>>V;
	S--, T--, U--, V--;
	for(ll i = 0;i < M;i++){
		ll a,b,c;
		cin>>a>>b>>c;
		a--, b--;
		v[a].push_back({b,c});
		v[b].push_back({a,c});
	}
	memset(distS,-1,sizeof(distS));
	dijkstra(S);
	memset(distT,-1,sizeof(distT));
	dijkstra(T);
	priority_queue<pair<pair<ll,pair<ll,ll> >,pair<ll,ll> >,vector<pair<pair<ll,pair<ll,ll> >,pair<ll,ll> > >,greater<pair<pair<ll,pair<ll,ll> >,pair<ll,ll> > > > pq;
	ll dist[N][3]; //not entered free path yet, currently inside free path, already exited free path
	memset(dist,-1,sizeof(dist));
	dist[U][0] = 0;
	pq.push({{0,{-1,0}},{U,0}});
	while(!pq.empty()){
		ll d = pq.top().first.first;
		ll p = pq.top().first.second.first;
		ll pw = pq.top().first.second.second;
		ll x = pq.top().second.first;
		ll type = pq.top().second.second;
		pq.pop();
		if(d != dist[x][type]){
			continue;
		}
		for(auto u : v[x]){
			if(type == 0){
				//enter free path
				if(min(distS[x] + u.second + distT[u.first],distT[x] + u.second + distS[u.first]) == distS[T]){
					if(dist[u.first][1] == -1 || dist[x][0] < dist[u.first][1]){
						dist[u.first][1] = dist[x][0];
						pq.push({{dist[u.first][1],{x,u.second}},{u.first,1}});
					}
				}
				//don't enter free path yet
				if(dist[u.first][0] == -1 || dist[x][0] + u.second < dist[u.first][0]){
					dist[u.first][0] = dist[x][0] + u.second;
					pq.push({{dist[u.first][0],{x,u.second}},{u.first,0}});
				}
			}else if(type == 1){
				//continue free path
				if(min(distS[p] + pw + u.second + distT[u.first],distT[p] + pw + u.second + distS[u.first]) == distS[T] && min(distS[x] + u.second + distT[u.first],distT[x] + u.second + distS[u.first]) == distS[T]){
					if(dist[u.first][1] == -1 || dist[x][1] < dist[u.first][1]){
						dist[u.first][1] = dist[x][1];
						pq.push({{dist[u.first][1],{x,u.second}},{u.first,1}});
					}
				}
				//leave free path
				if(dist[u.first][2] == -1 || dist[x][1] + u.second < dist[u.first][2]){
					dist[u.first][2] = dist[x][1] + u.second;
					pq.push({{dist[u.first][2],{x,u.second}},{u.first,2}});
				}
			}else if(type == 2){
				if(dist[u.first][2] == -1 || dist[x][2] + u.second < dist[u.first][2]){
					dist[u.first][2] = dist[x][2] + u.second;
					pq.push({{dist[u.first][2],{x,u.second}},{u.first,2}});
				}
			}
		}
	}
	ll ans = 1e18;
	if(dist[V][0] != -1) ans = min(ans,dist[V][0]);
	if(dist[V][1] != -1) ans = min(ans,dist[V][1]);
	if(dist[V][2] != -1) ans = min(ans,dist[V][2]);
	cout<<ans<<'\n';
}
