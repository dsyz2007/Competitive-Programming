#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (500005)
ll N,Q;
ll fw[MAXN];
void update(int x,ll nval) {
	for(;x<MAXN;x+=x&(-x)) fw[x]+=nval;
}
ll aaa(int x) {
    ll res = 0;
    for(;x;x-=x&(-x)) res += fw[x];
    return res;
}
ll sum(int a,int b) {
    return aaa(b) - aaa(a-1);
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N>>Q;
	ll arr[N];
	vector<pair<pair<ll,ll>,ll> > queries;
	vector<ll> d;
	for(ll i = 0;i < N;i++){
		cin>>arr[i];
		d.push_back(arr[i]);
	}
	sort(d.begin(),d.end());
	d.resize(unique(d.begin(),d.end()) - d.begin());
	for(ll i = 0;i < N;i++) arr[i] = (lower_bound(d.begin(), d.end(), arr[i]) - d.begin() + 1);
	for(ll i = 0;i < Q;i++){
		ll L,R;
		cin>>L>>R;
		L--;
		R--;
		queries.push_back(make_pair(make_pair(R,L),i));
	}
	sort(queries.begin(),queries.end());
	vector<ll> prev[N + 5];
	ll left[N];
	memset(left,-1,sizeof(left));
	for(ll i = 0;i < N;i++){
		if(!prev[arr[i]].empty()){
			left[i] = prev[arr[i]].back();
		}else{
			left[i] = -1;
		}
		prev[arr[i]].push_back(i);
	}
	ll ptr = -1;
	ll ans[Q];
	memset(ans,0,sizeof(ans));
	for(auto u : queries){
		ll R = u.first.first;
		ll L = u.first.second;
		ll index = u.second;
		for(ll i = ptr + 1;i <= R;i++){
			if(left[i] != -1){
				update(left[i] + 1,1);
				if(left[left[i]] != -1){
					update(left[left[i]] + 1,-2);
					if(left[left[left[i]]] != -1){
						update(left[left[left[i]]] + 1,1);
					}
				}
			}
		}
		ptr = R;
		ans[index] = sum(L + 1,R + 1);
	}
	for(ll i = 0;i < Q;i++){
		cout<<ans[i]<<'\n';
	}
}
