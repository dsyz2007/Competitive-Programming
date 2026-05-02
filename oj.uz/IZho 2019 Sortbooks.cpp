#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
struct node {
	ll s,e,m,v;
	node *l, *r;
	node(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e)>>1;
		v = 0;
		if(s != e){
			l = new node(s,m);
			r = new node(m + 1,e);
		}
	}
	void update(ll x,ll val){
		if(s == e){
			v = max(v,val);
			return;
		}else{
			if(x > m) r -> update(x,val);
			else l -> update(x,val);
			v = max(l -> v,r -> v);
		}
	}
	ll rmaxq(ll x,ll y){
		if(s == x && e == y){
			return v;
		}else{
			if(x > m) return r -> rmaxq(x,y);
			else if(y <= m) return l -> rmaxq(x,y);
			else return max(l -> rmaxq(x,m),r -> rmaxq(m + 1,y));
		}
	}
} *root;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,M;
	cin>>N>>M;
	root = new node(0,N + 5);
	ll W[N];
	for(ll i = 0;i < N;i++){
		cin>>W[i];
	}
	vector<pair<pair<ll,ll>,pair<ll,ll> > > queries; //{{R,L},{K,ith query}}
	for(ll i = 0;i < M;i++){
		ll L,R,K;
		cin>>L>>R>>K;
		L--;
		R--;
		queries.push_back({{R,L},{K,i}});
	}
	sort(queries.begin(),queries.end());
	ll ans[M];
	memset(ans,0,sizeof(ans));
	ll Rptr = -1;
	deque<pair<ll,ll> > dq;
	for(ll q = 0;q < queries.size();q++){
		ll L = queries[q].first.second;
		ll R = queries[q].first.first;
		ll K = queries[q].second.first;
		ll index = queries[q].second.second;
		while(Rptr < R){
			Rptr++;
			while(!dq.empty() && dq.front().first <= W[Rptr]){
				dq.pop_front();
			}
			if(!dq.empty()){
				ll Wj = dq.front().first;
				ll j = -1 * dq.front().second;
				root -> update(j,Wj + W[Rptr]);
			}
			while(!dq.empty() && dq.front().first <= W[Rptr]){
				dq.pop_front();
			}
			dq.push_front(make_pair(W[Rptr],-Rptr));
		}
		ll maximum = root -> rmaxq(L,R);
		if(maximum <= K){
			ans[index] = 1;
		}else{
			ans[index] = 0;
		}
	}
	for(ll i = 0;i < M;i++){
		cout<<ans[i]<<'\n';
	}
}
