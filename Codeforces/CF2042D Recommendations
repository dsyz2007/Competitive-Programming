#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
struct node{
	ll s,e,m,v;
	node *l, *r;
	node(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) / 2;
		v = -1;
		if(s != e){
			l = new node(s,m);
			r = new node(m + 1,e);	 
		}
	}
	void update(ll x,ll nval){
		if(s == e){
			v = nval;
			return;
		}else{
			if(x > m) r -> update(x,nval);
			else l -> update(x,nval);
			v = max(l->v,r->v);
		}
	}
	ll rmq(ll x,ll y){
		if(s == x && e == y){
			return v;
		}else{
			if(x > m) return r -> rmq(x,y);
			else if(y <= m) return l -> rmq(x,y);
			else return max(l -> rmq(x,m),r -> rmq(m + 1,y));
		}
	}
} *root;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll t;
	cin>>t;
	while(t--){
		ll N;
		cin>>N;
		root = new node(0,2 * N + 1);
		pair<pair<ll,ll>,ll> arr[N];
		vector<ll> d;
		for(ll i = 0;i < N;i++){
			cin>>arr[i].first.first>>arr[i].first.second;
			arr[i].second = i;
			d.push_back(arr[i].first.first);
			d.push_back(arr[i].first.second);
		}
		sort(d.begin(),d.end());
		d.resize(unique(d.begin(),d.end()) - d.begin());
		for(ll i = 0;i < N;i++){
			arr[i].first.first = lower_bound(d.begin(),d.end(),arr[i].first.first) - d.begin();
			arr[i].first.second = lower_bound(d.begin(),d.end(),arr[i].first.second) - d.begin();
		}
		vector<pair<ll,pair<bool,ll> > > sweep;
		for(ll i = 0;i < N;i++){
			sweep.push_back({arr[i].first.first,{0,arr[i].second}});
			sweep.push_back({arr[i].first.second,{1,arr[i].second}});
		}
		sort(sweep.begin(),sweep.end());
		ll ans[N];
		memset(ans,0,sizeof(ans));
		multiset<ll> endpoint[2 * N + 1];
		multiset<ll> active;
		deque<pair<ll,pair<bool,ll> > > dq;
		for(ll i = 0;i < sweep.size();i++){
			dq.push_back(sweep[i]);
			if(i != sweep.size() - 1 && sweep[i].first == sweep[i + 1].first && sweep[i].second.first == 0 && sweep[i + 1].second.first == 0){
				continue;
			}
			multiset<ll> endpoints;
			ll maxendpoint = 0;
			for(auto u : dq){
				ll val = u.first;
				bool type = u.second.first;
				ll ind = u.second.second;
				maxendpoint = max(maxendpoint,arr[ind].first.second);
				endpoints.insert(arr[ind].first.second);
			}
			ll freqmaxendpoint = 0;
			for(auto u : dq){
				ll val = u.first;
				bool type = u.second.first;
				ll ind = u.second.second;
				if(arr[ind].first.second == maxendpoint){
					freqmaxendpoint++;
				}
			}
			for(auto u : dq){
				ll val = u.first;
				bool type = u.second.first;
				ll ind = u.second.second;
				while(!active.empty() && *active.begin() < val){
					active.erase(active.begin());
				}
				if(type == 0){ //open
					ll rightmostopen = root -> rmq(arr[ind].first.second,2 * N + 1);
					if(rightmostopen != -1 && arr[ind].first.second == maxendpoint && freqmaxendpoint == 1){
						ans[ind] += (d[val] - d[rightmostopen]);
					}
					
					ll add = 1e18;
					endpoints.erase(endpoints.find(arr[ind].first.second));
					if(!endpoints.empty()){
						auto it = endpoints.lower_bound(arr[ind].first.second);
						if(it != endpoints.end()){
							add = min(add,d[*it] - d[arr[ind].first.second]);
						}
					}
					endpoints.insert(arr[ind].first.second);
					if(!active.empty()){
						auto it = active.lower_bound(arr[ind].first.second);
						if(it != active.end()){
							add = min(add,(d[*it] - d[arr[ind].first.second]));
						}
					}
					if(add != 1e18) ans[ind] += add;
					
					active.insert(arr[ind].first.second);
					endpoint[arr[ind].first.second].insert(arr[ind].first.first);
					root -> update(arr[ind].first.second,*prev(endpoint[arr[ind].first.second].end()));
				}else{ //close
					active.erase(active.find(arr[ind].first.second));
					endpoint[arr[ind].first.second].erase(endpoint[arr[ind].first.second].find(arr[ind].first.first));
					if(endpoint[arr[ind].first.second].empty()){
						root -> update(arr[ind].first.second,-1);
					}else{
						root -> update(arr[ind].first.second,*prev(endpoint[arr[ind].first.second].end()));
					}
				}
			}
			dq.clear();
		}
		for(ll i = 0;i < N;i++){
			cout<<ans[i]<<'\n';
		}
	}
}
