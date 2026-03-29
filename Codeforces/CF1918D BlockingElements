#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (1000005)
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll t;
	cin>>t;
	while(t--){
		ll N;
		cin>>N;
		ll arr[N];
		ll high = 1e18;
		ll low = -1;
		for(ll i = 0;i < N;i++){
			cin>>arr[i];
			low = max(low,arr[i] - 1);
		}
		while(high - low > 1){
			ll mid = (high + low) / 2;
			multiset<pair<ll,ll> > s;
			ll dp[N]; //block at pos i
			ll Lptr = 0, cur = 0, psum = 0;
			for(ll i = 0;i < N;i++){
				dp[i] = 1e18;
			}
			for(ll i = 0;i < N;i++){
				while(Lptr < i && cur - arr[Lptr] > mid){
					cur -= arr[Lptr];
					s.erase(s.find({dp[Lptr],Lptr}));
					Lptr++;
				}
				ll prev = 0;
				if(!s.empty() && psum > mid) prev = s.begin()->first;
				dp[i] = prev + arr[i];
				cur += arr[i];
				psum += arr[i];
				s.insert({dp[i],i});
			}
			ll sufsum = 0;
			ll mini = 1e18;
			for(ll i = N - 1;i >= 0;i--){
				if(sufsum > mid) break;
				mini = min(mini,dp[i]);
				sufsum += arr[i];
			}
			if(mini <= mid){
				high = mid;
			}else{
				low = mid;
			}
		}
		cout<<high<<'\n';
	}
}
