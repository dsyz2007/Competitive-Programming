#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
ll N,D;
struct node1 {
	ll s,e,m,v;
	node1 *l, *r;
	node1(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) / 2;
		v = 0;
		if(s != e){
			l = new node1(s,m);
			r = new node1(m + 1,e);
		}
	}
	void update(ll x,ll nval){
		if(s == e){
			v = nval;
			return;
		}else{
			if(x > m) r -> update(x,nval);
			else l -> update(x,nval);
			v = max(l -> v,r -> v);
		}
	}
	ll bs(ll x){ //binary serach for leftmost position with v > x
		if(s == e){
			if(v <= x) return N + 5;
			else return s;
		}else{
			if(l->v > x) return l -> bs(x);
			else if(r->v > x) return r -> bs(x);
			else return N + 5;
		}
	}
} *root1;
struct node2 {
	ll s,e,m,lazy,v;
	node2 *l, *r;
	node2(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) / 2;
		lazy = -1;
		v = 0;
		if(s != e){
			l = new node2(s,m);
			r = new node2(m + 1,e);
		}
	}
	void propo(){
		if(lazy == -1) return;
		v = max(v,lazy);
		if(s != e){
			l->lazy = max(l->lazy,lazy);
			r->lazy = max(r->lazy,lazy);
		}
		lazy = -1;
	}
	void update(ll x,ll y,ll nval){
		propo();
		if(s == x && e == y){
			lazy = max(lazy,nval);
			return;
		}else{
			if(x > m) r -> update(x,y,nval);
			else if(y <= m) l -> update(x,y,nval);
			else l -> update(x,m,nval), r -> update(m + 1,y,nval);
			l -> propo(), r -> propo();
			v = max(l -> v,r -> v);
		}
	}
	ll query(ll x){
		propo();
		if(s == e){
			return v;
		}else{
			if(x > m) return r -> query(x);
			else return l -> query(x);
		}
	}
} *root2;
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>D;
	ll mini[N], rightmost[N];
	pair<ll,ll> arr[N];
	root1 = new node1(0,N + 5);
	root2 = new node2(0,N + 5);
	for(ll i = 0;i < N;i++){
		cin>>arr[i].first;
		arr[i].second = -i;
	}
	multiset<ll> s;
	for(ll i = 0;i < N;i++){
		s.insert(arr[i].first);
		if(i >= D) s.erase(s.find(arr[i - D].first));
		mini[i] = *s.begin();
	}
	for(ll i = N - 1;i >= 0;i--){
		if(i + D < N) root1 -> update(i + D,mini[i + D]); //update (i+D)th position with value mini[i+D]
		rightmost[i] = root1 -> bs(arr[i].first);
	}
	sort(arr,arr + N); //increasing A[i], if tie (same A[i]) from right to left
	ll dp[N];
	ll ans = 0;
	for(auto u : arr){ //loop in order of increasing A[i], if tie (same A[i]) from right to left
		ll ind = -1 * u.second;
		dp[ind] = root2 -> query(ind) + 1;
		root2 -> update(ind,rightmost[ind],dp[ind]); //future states can only come from ind if their original position <= rightmost[ind]
		ans = max(ans,dp[ind]);
	}
	cout<<ans<<'\n';
}
