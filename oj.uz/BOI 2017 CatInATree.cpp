#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (200005)
ll N,D;
vector<pair<ll,ll> > sortbydepth;
vector<pair<ll,ll> > DIST[MAXN];
vector<pair<ll,ll> > v[MAXN];
ll sub[MAXN], par[MAXN], lvl[MAXN], dist[MAXN][20], m[MAXN];
bool cannot[MAXN];
void calcdepth(ll x,ll p,ll level){
	sortbydepth.push_back({level,x});
	for(auto u : v[x]){
		if(u.first != p){
			calcdepth(u.first,x,level + 1);
		}
	}
}
ll dfs1(ll x,ll p,ll l){
	sub[x] = 1;
	for(auto u : v[x]){
		if(u.first != p && lvl[u.first] == -1){ //unvisited
			sub[x] += dfs1(u.first,x,l);
		}
	}
	return sub[x];
}
ll dfs2(ll x,ll p,ll siz){ //siz is total size of this centroid tree 
	for(auto u : v[x]){
		if(u.first != p && lvl[u.first] == -1 && sub[u.first] > siz / 2){
			return dfs2(u.first,x,siz); //remember that siz remains constant
		}
	}
	return x;
}
void dfsdist(ll x,ll p,ll centroid,ll curlvl,ll curdist){
	dist[x][curlvl] = curdist;
	DIST[centroid].push_back({curdist,x});
	for(auto u : v[x]){
		if(u.first != p && lvl[u.first] == -1){ //unvisited
			dfsdist(u.first,x,centroid,curlvl,curdist + u.second);
			//Note: curlvl is unchanged since we are moving down so
			//the relative lvl has already changed
		}
	}
}
void build(ll x,ll p,ll l){
	ll siz = dfs1(x,p,l);
	ll cent = dfs2(x,p,siz);
	if(p == -1) p = cent;
	par[cent] = p;
	lvl[cent] = l;
	dfsdist(cent,-1,cent,l,0);
	sort(DIST[cent].begin(),DIST[cent].end(),greater<pair<ll,ll> >());
	for(auto u : v[cent]){
		if(lvl[u.first] == -1){ //unvisited
			build(u.first,cent,l + 1);
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>D;
	for(ll i = 1;i < N;i++){
		ll p;
		cin>>p;
		v[p].push_back({i,1});
		v[i].push_back({p,1});
	}
	calcdepth(0,-1,0);
	sort(sortbydepth.begin(),sortbydepth.end(),greater<pair<ll,ll> >());
	for(ll i = 0;i < MAXN;i++){
		for(ll j = 0;j < 20;j++){
			dist[i][j] = 1e18;
		}
	}
	memset(lvl,-1,sizeof(lvl)); //need lvl to find dist[i][lvl]
	build(0,-1,0);
	for(ll i = 0;i < MAXN;i++){
		m[i] = 1e18;
	}
	ll ans = 0;
	for(auto u : sortbydepth){
		if(cannot[u.second]) continue;
		ll x = u.second;
		while(true){
			ll distjumped = dist[u.second][lvl[x]];
			while(!DIST[x].empty()){
				if(DIST[x].back().first + distjumped < D){ //node DIST[x].back().second cannot be picked as distance < D from a node that is already selected, we can greedily prove that it is not optimal to delete the selected node (with greater depth) and replace it with node DIST[x].back().second (with lower depth)
					cannot[DIST[x].back().second] = true;
					DIST[x].pop_back();
				}else{
					break;
				}
			}
			if(par[x] == x) break; //x is the root node in the centroid tree
			x = par[x]; //in the centroid tree, height is at most log2(N) so node x has at most log2(N) ancestors in total
		}
		ans++;
	}
	cout<<ans<<'\n';
}
