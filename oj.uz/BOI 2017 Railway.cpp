#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (100005)
ll N,M,K;
vector<pair<ll,ll> > v[MAXN]; //node b, index of edge
vector<ll> ans;
set<pair<ll,ll> > s[MAXN];
ll parent[20][MAXN], depth[MAXN], dist[MAXN];
bool visited[MAXN];
void distdfs(ll x){
	visited[x] = 1;
	for(auto u : v[x]){
		if(visited[u.first] == 0){
			dist[u.first] = dist[x] + 1;
			visited[u.first] = 1;
			distdfs(u.first);
		}
	}
}
void dfs1(ll x,ll nodeparent,ll nodedepth){
	parent[0][x] = nodeparent;
	depth[x] = nodedepth;
	for(ll i = 0;i < v[x].size();i++){
		if(v[x][i].first != nodeparent){
			dfs1(v[x][i].first,x,nodedepth + 1);
		}
	}
}
void lcainit(){
	for(ll i = 1;i < 20;i++){
		for(ll j = 0;j < N;j++){
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}
}
ll lca(ll u,ll v){
	if(depth[u] > depth[v]){
		swap(u,v);
	}
	ll diff = depth[v] - depth[u];
	for(ll i = 0;i < 20;i++){
		if(diff & (1<<i)){
			v = parent[i][v];
		} 
	}
	if(u == v){
		return u;
	} 
	for(ll i = 19;i >= 0;i--){
		if(parent[i][u] != parent[i][v]){
			u = parent[i][u];
			v = parent[i][v];
		}
	}
	return parent[0][u];
}
void dfs2(ll x,ll p){
	ll parentedge = -1;
	for(auto u : v[x]){
		if(u.first != p){
			dfs2(u.first,x);
			if(s[u.first].size() > s[x].size()) swap(s[u.first],s[x]); //swap sets is O(1)
			//swapping 2 sets, vectors, maps are O(1) so use these data structures
			//for pbds, it is a bit different syntax: a.swap(b) is O(1)
			s[x].insert(s[u.first].begin(),s[u.first].end());
		}else{
			parentedge = u.second;
		}
	}
	while(!s[x].empty() && s[x].begin()->first == -1 * depth[x]){
		s[x].erase(s[x].begin());
	}
	if(s[x].size() >= K && parentedge != -1){
		ans.push_back(parentedge);
	}
}
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>M>>K;
	for(ll i = 0;i < N - 1;i++){
		ll a,b;
		cin>>a>>b;
		a--, b--;
		v[a].push_back({b,i});
		v[b].push_back({a,i});
	}
	dist[0] = 0;
	visited[0] = 1;
	distdfs(0);
	dfs1(0,0,0);
	lcainit();
	for(ll i = 0;i < M;i++){
		ll S;
		cin>>S;
		ll LCA = -1;
		ll A[S];
		for(ll j = 0;j < S;j++){
			cin>>A[j];
			A[j]--;
			if(j == 0){
				LCA = A[j];
			}else{
				LCA = lca(LCA,A[j]);
			}
		}
		for(ll j = 0;j < S;j++){
			s[A[j]].insert({-depth[LCA],i});
		}
	}
	dfs2(0,-1);
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(auto u : ans){
		cout<<u + 1<<" ";
	}
	cout<<'\n';
}
