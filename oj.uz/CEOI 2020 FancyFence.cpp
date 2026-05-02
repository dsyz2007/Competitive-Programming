#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
ll ans = 0, cursum = 0, mod = 1e9 + 7;
ll parent[MAXN], SIZE[MAXN];
ll tri(ll h){
	return ((h + 1) * h) / 2ll; //the triangle sum formula is N*(N + 1) / 2 (basically the sum of 1,2,...,N)
}
ll find_set(ll x){
	if(parent[x] == x) return x;
	parent[x] = find_set(parent[x]);
	return parent[x];
}
bool same_set(ll x,ll y){
	return find_set(x) == find_set(y);
}
void merge_set(ll x,ll y){
	if(same_set(x,y)) return;
	ll Xsize = SIZE[find_set(x)], Ysize = SIZE[find_set(y)];
	cursum += (Xsize * Ysize);
	cursum %= mod;
	ll totalsize = Xsize + Ysize;
	totalsize %= mod;
	parent[find_set(x)] = find_set(y);
	SIZE[find_set(x)] = totalsize;
}
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N;
	cin>>N;
	pair<pair<ll,ll>,ll> arr[N];
	for(ll i = 0;i < N;i++){
		cin>>arr[i].first.first; //H[i]
	}
	for(ll i = 0;i < N;i++){
		cin>>arr[i].first.second; //W[i]
	}
	for(ll i = 0;i < N;i++){
		arr[i].second = i;
		parent[i] = i;
		SIZE[i] = arr[i].first.second;
	}
	set<ll,greater<ll> > heights;
	for(ll i = 0;i < N;i++){
		heights.insert(arr[i].first.first);
	}
	sort(arr,arr + N,greater<pair<pair<ll,ll>,ll> >());
	bool can[N];
	memset(can,0,sizeof(can));
	ll ptr = -1;
	for(auto h : heights){
		cursum = 0;
		while(ptr + 1 < N && arr[ptr + 1].first.first == h){
			ptr++;
			ll ind = arr[ptr].second;
			can[ind] = 1;
			cursum += (((arr[ptr].first.second + 1) * arr[ptr].first.second) / 2);
			cursum %= mod;
			if(ind >= 1 && can[ind - 1]){
				merge_set(ind - 1,ind);
			}
			cursum %= mod;
			if(ind < N - 1 && can[ind + 1]){
				merge_set(ind,ind + 1);
			}
			cursum %= mod;
		}
		ans += ((cursum % mod) * (tri(h) % mod));
		ans %= mod;
	}
	cout<<ans % mod<<'\n';
}
