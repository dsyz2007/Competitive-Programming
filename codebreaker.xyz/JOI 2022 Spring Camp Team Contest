#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
struct node{
	ll s,e,m;
	pair<ll,ll> v;
	node *l = nullptr,*r = nullptr; //remember to set to nullptr (if not it might RTE)
	node(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) / 2;
		v = {-1e18,s};
	}
	void create(){
		if(l == nullptr && s != e){
			l = new node(s,m);
			r = new node(m + 1,e);
		}
	}
	void update(ll x,ll nval){
		if(s == e){
			v.first = max(v.first,nval);
		}else{
			create();
			if(x > m) r -> update(x,nval);
			else l -> update(x,nval);
			v = max(l->v,r->v);
		}
	}
	pair<ll,ll> rmq(ll x,ll y){
		create();
		if(s == x && e == y){
			return v;
		}else{
			if(x > m) return r->rmq(x,y);
			else if(y <= m) return l->rmq(x,y);
			else return max(l->rmq(x,m),r->rmq(m + 1,y));
		}
	}
} *rootBindtest, *rootCindtest, *rootBind, *rootCind;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N;
	cin>>N;
	rootBindtest = new node(0,3*N + 5);
	rootCindtest = new node(0,3*N + 5);
	rootBind = new node(0,3*N + 5);
	rootCind = new node(0,3*N + 5);
	pair<ll,pair<ll,ll> > arr[N]; //X, Y, Z
	vector<ll> d;
	for(ll i = 0;i < N;i++){
		cin>>arr[i].first>>arr[i].second.first>>arr[i].second.second;
		d.push_back(arr[i].first);
		d.push_back(arr[i].second.first);
		d.push_back(arr[i].second.second);
	}
	sort(d.begin(),d.end());
	d.resize(unique(d.begin(),d.end()) - d.begin());
	for(ll i = 0;i < N;i++){
		arr[i].first = lower_bound(d.begin(),d.end(),arr[i].first) - d.begin() + 1;
		arr[i].second.first = lower_bound(d.begin(),d.end(),arr[i].second.first) - d.begin() + 1;
		arr[i].second.second = lower_bound(d.begin(),d.end(),arr[i].second.second) - d.begin() + 1;
	}
	sort(arr,arr + N);
	deque<pair<ll,pair<ll,ll> > > waiting;
	ll ans = -1e18;
	for(ll i = 0;i < N;i++){
		while(!waiting.empty() && waiting.front().first < arr[i].first){
			ll bestC = -1e18;
			if(waiting.front().second.first > 0){
				bestC = rootBindtest -> rmq(0,waiting.front().second.first - 1).first;
			}
			if(bestC != -1e18 && bestC > waiting.front().second.second){
				rootBind -> update(waiting.front().second.first,waiting.front().second.first + bestC);
			}
			
			ll bestB = -1e18;
			if(waiting.front().second.second > 0){
				bestB = rootCindtest -> rmq(0,waiting.front().second.second - 1).first;
			}
			if(bestB != -1e18 && bestB > waiting.front().second.first){
				rootCind -> update(waiting.front().second.second,waiting.front().second.second + bestB);
			}
			
			rootBindtest -> update(waiting.front().second.first,waiting.front().second.second);
			rootCindtest -> update(waiting.front().second.second,waiting.front().second.first);
			waiting.pop_front();
		}
		if(arr[i].second.first > 0){
			pair<ll,ll> maxiBind = rootBind -> rmq(arr[i].second.first + 1,3*N + 5);
			if(maxiBind.first > 0){
				ll B = maxiBind.second;
				ll C = maxiBind.first - maxiBind.second;
				if(C > arr[i].second.second){
					ans = max(ans,d[arr[i].first - 1] + d[B - 1] + d[C - 1]); //need to minus 1 cos when I discretised, I made it 1-indexed to make it easier to implement
				}
			}
		}
		if(arr[i].second.second > 0){
			pair<ll,ll> maxiCind = rootCind -> rmq(arr[i].second.second + 1,3*N + 5);
			if(maxiCind.first > 0){
				ll C = maxiCind.second;
				ll B = maxiCind.first - maxiCind.second;
				if(B > arr[i].second.first){
					ans = max(ans,d[arr[i].first - 1] + d[B - 1] + d[C - 1]); //need to minus 1 cos when I discretised, I made it 1-indexed to make it easier to implement
				}
			}
		}
		waiting.push_back(arr[i]);
	}
	if(ans == -1e18) cout<<-1<<'\n';
	else cout<<ans<<'\n';
}
