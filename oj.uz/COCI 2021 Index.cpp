#include <bits/stdc++.h>
using namespace std;
using ll = int;
#define MAXN (200005)
struct node {
	ll s,e,m,v;
	node *l, *r;
	node(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) >> 1;
		v = 0;
		if(s != e){
			l = new node(s,m);
			r = new node(m + 1,e);
		}
	}
	node(node *u){
		s = u->s, e = u->e, m = u->m;
		v = u->v;
		l = u->l, r = u->r;
	}
	void update(ll x,ll val){
		if(s == e){
			v += val;
			return;
		}else{
			if(x > m){
				r = new node(r);
				r -> update(x,val);
			}else{
				l = new node(l);
				l -> update(x,val);
			}
			v = l->v + r->v;
		}
	}
	ll query(ll x,ll y){
		if(s == x && e == y){
			return v;
		}else{
			if(x > m) return r -> query(x,y);
			else if(y <= m) return l -> query(x,y);
			else return l -> query(x,m) + r -> query(m + 1,y);
		}
	}
} *root[MAXN];
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,Q;
	cin>>N>>Q;
	ll arr[N];
	deque<pair<ll,ll> > p;
	for(ll i = 0;i < N;i++){
		cin>>arr[i];
		p.push_back({arr[i],i});
	}
	sort(p.begin(),p.end(),greater<pair<ll,ll> >());
	root[MAXN - 1] = new node(0,N - 1);
	for(ll i = MAXN - 2;i >= 0;i--){
		root[i] = new node(root[i + 1]);
		while(!p.empty() && p.front().first >= i){
			ll val = p.front().first;
			ll ind = p.front().second;
			root[i] -> update(ind,1);
			p.pop_front();
		}
	}
	for(ll q = 0;q < Q;q++){
		ll l,r;
		cin>>l>>r;
		l--;
		r--;
		ll high = MAXN;
		ll low = 0;
		while(high - low > 1){
			ll mid = (high + low) / 2;
			if(root[mid] -> query(l,r) >= mid){
				low = mid;
			}else{
				high = mid;
			}
		}
		cout<<low<<'\n';
	}
}
