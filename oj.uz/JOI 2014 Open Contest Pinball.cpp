#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (300005)
struct node{
	ll s,e,m,v,lazyadd;
	node *l,*r;
	node(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) / 2;
		v = 1e18;
		lazyadd = 1e18;
		if(s != e){
			l = new node(s,m);
			r = new node(m + 1,e);
		}
	}
	ll value(){
		if(s == e){
			v = min(v,lazyadd);
			return v;
		}
		v = min(v,lazyadd);
		r->lazyadd = min(r -> lazyadd,lazyadd);
		l->lazyadd = min(l -> lazyadd,lazyadd);
		return v;
	}
	void update(ll x,ll y,ll val){
		if(s == x && e == y) lazyadd = min(lazyadd,val);
		else{
			if(x > m) r -> update(x,y,val);
			else if(y <= m) l -> update(x,y,val);
			else l -> update(x,m,val), r -> update(m + 1,y,val);
			v = min(l->value(),r->value());
		}
	}
	ll rmq(ll x,ll y){
		value();
		if(s == x && e == y) return value();
		if(x > m) return r -> rmq(x,y);
		if(y <= m) return l -> rmq(x,y);
		return min(l -> rmq(x,m),r -> rmq(m + 1,y)); 
	}
} *root;
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll M,N;
	cin>>M>>N;
	root = new node(0,MAXN);
	pair<ll,ll> range[M];
	ll A[M], B[M], C[M], D[M];
	vector<ll> d;
	for(ll i = 0;i < M;i++){
		cin>>range[i].first>>range[i].second>>C[i]>>D[i];
		d.push_back(range[i].first);
		d.push_back(range[i].second);
		d.push_back(C[i]);
		A[i] = range[i].first;
		B[i] = range[i].second;
	}
	sort(d.begin(),d.end());
	d.resize(unique(d.begin(),d.end()) - d.begin());
	for(ll i = 0;i < M;i++){
		range[i].first = lower_bound(d.begin(),d.end(),range[i].first) - d.begin();
		range[i].second = lower_bound(d.begin(),d.end(),range[i].second) - d.begin();
		C[i] = lower_bound(d.begin(),d.end(),C[i]) - d.begin();
	}
	ll dp1[M]; //start from column 1
	for(ll i = 0;i < M;i++){
		if(A[i] == 1) dp1[i] = D[i];
		else dp1[i] = 1e18;
	}
	for(ll i = 0;i < M;i++){
		ll prev = root -> rmq(range[i].first,range[i].second);
		if(A[i] == 1){
			dp1[i] = D[i];
		}else{
			if(prev < 1e18) dp1[i] = prev + D[i];
		}
		if(dp1[i] < 1e18) root -> update(C[i],C[i],dp1[i]);
	}
	root = new node(0,MAXN);
	ll dpN[M]; //start from column N
	for(ll i = 0;i < M;i++){
		if(B[i] == N) dpN[i] = D[i];
		else dpN[i] = 1e18;
	}
	for(ll i = 0;i < M;i++){
		ll prev = root -> rmq(range[i].first,range[i].second);
		if(B[i] == N){
			dpN[i] = D[i];
		}else{
			if(prev < 1e18) dpN[i] = prev + D[i];
		}
		if(dpN[i] < 1e18) root -> update(C[i],C[i],dpN[i]);
	}
	ll ans = 2e18 + 5;
	for(ll i = 0;i < M;i++){
		if(dp1[i] < 1e18 && dpN[i] < 1e18){
			ans = min(ans,dp1[i] + dpN[i] - D[i]);
		}
	}
	if(ans >= 1e18) cout<<-1<<'\n';
	else cout<<ans<<'\n';
}
