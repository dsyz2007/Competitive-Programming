#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,K,R;
	cin>>N>>K>>R;
	ll arr[N];
	for(ll i = 0;i < N;i++){
		cin>>arr[i];		
	}
	ll cnt[K];
	memset(cnt,0,sizeof(cnt));
	ll atleast[K];
	memset(atleast,0,sizeof(atleast));
	set<pair<ll,ll> > shortage;
	for(ll i = 0;i < R;i++){
		ll b,q;
		cin>>b>>q;
		atleast[b] = q;
		shortage.insert({q,b});
	}
	ll minimum = 1e18;
	ll l = 0;
	for(ll r = 0;r < N;r++){
		if(cnt[arr[r]] < atleast[arr[r]]){
			auto it = shortage.find({atleast[arr[r]] - cnt[arr[r]],arr[r]});
			shortage.erase(it);
			cnt[arr[r]]++;
			if(cnt[arr[r]] < atleast[arr[r]]){
				shortage.insert({atleast[arr[r]] - cnt[arr[r]],arr[r]});
			}
		}else{
			cnt[arr[r]]++;
		}
		if(shortage.empty()){
			while(l < r && cnt[arr[l]] > atleast[arr[l]]){
				cnt[arr[l]]--;
				l++;
			}
			minimum = min(minimum,r - l + 1);
		}
	}
	if(!shortage.empty()) cout<<"impossible"<<'\n';
	else cout<<minimum<<'\n';
}
