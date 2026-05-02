#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (100005)
ll N,K;
struct fenwick {
	ll fw[MAXN], fw2[MAXN];
	fenwick() {
		memset(fw,0,sizeof(fw));
		memset(fw2,0,sizeof(fw2));
	}
	void update(ll x,ll y,ll v){
		y++;
		for(ll tx = x;tx <= N;tx += tx&(-tx)) fw[tx] += v,fw2[tx] -= v * (x - 1);
		for(ll ty = y;ty <= N;ty += ty&(-ty)) fw[ty] -= v,fw2[ty] += v * (y - 1);
	}
	long long sum(long long x){
		ll ans = 0;
		for(ll tx = x;tx;tx -= tx&(-tx)){
			ans += (fw[tx] * x) + fw2[tx];
		}
		return ans;
	}
	long long range_sum(long long x,long long y){
		return sum(y) - sum(x - 1);
	}
} front, middle, back;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	//note that everything is 1-indexed
	cin>>N>>K;
	ll arr[N + 1];
	for(ll i = 1;i <= N;i++){
		cin>>arr[i];
	}
	arr[0] = 0;
	ll pre[N + 1], suf[N + 1];
	memset(pre,0,sizeof(pre));
	memset(suf,0,sizeof(suf));
	for(ll i = 1;i <= N;i++){
		pre[i] = arr[i] * i;
	}
	for(ll i = N;i >= 1;i--){
		suf[i] = (arr[i] * (N - i + 1));
	}
	for(ll i = 1;i <= N;i++){
		front.update(i,i,pre[i]);
		middle.update(i,i,arr[i]);
		back.update(i,i,suf[i]);
	}
	ll Q;
	cin>>Q;
	for(ll q = 0;q < Q;q++){
		ll t;
		cin>>t;
		if(t == 1){ //1-indexed
			ll index[K];
			for(ll i = 0;i < K;i++){
				cin>>index[i];
			}
			for(ll i = 0;i < K - 1;i++){
				front.update(index[i],index[i],index[i] * -arr[index[i]] + index[i] * arr[index[i + 1]]);
				back.update(index[i],index[i],(N - index[i] + 1) * -arr[index[i]] + (N - index[i] + 1) * arr[index[i + 1]]);
				middle.update(index[i],index[i],arr[index[i + 1]] - arr[index[i]]);
			}
			front.update(index[K - 1],index[K - 1],index[K - 1] * -arr[index[K - 1]] + index[K - 1] * arr[index[0]]);
			back.update(index[K - 1],index[K - 1],(N - index[K - 1] + 1) * -arr[index[K - 1]] + (N - index[K - 1] + 1) * arr[index[0]]);
			middle.update(index[K - 1],index[K - 1],arr[index[0]] - arr[index[K - 1]]);
			ll first = arr[index[0]];
			for(ll i = 1;i < K;i++){
				arr[index[i - 1]] = arr[index[i]];
				pre[index[i - 1]] = index[i - 1] * arr[index[i - 1]];
				suf[index[i - 1]] = (N - index[i - 1] + 1) * arr[index[i - 1]];
			}
			arr[index[K - 1]] = first;
			pre[index[K - 1]] = index[K - 1] * arr[index[K - 1]];
			suf[index[K - 1]] = (N - index[K - 1] + 1) * arr[index[K - 1]];
		}else if(t == 2){ //1-indexed
			ll l,r,m;
			cin>>l>>r>>m;
			ll sum1 = 0, sum2 = 0,sum3 = 0;
			if((r - l + 1) - m > 0) sum1 += front.range_sum(l,l + ((r - l + 1) - m) - 1) - (l - 1) * middle.range_sum(l,l + ((r - l + 1) - m) - 1);
			if((r - l + 1) - m > 0) sum3 += back.range_sum(r - ((r - l + 1) - m) + 1,r) - (N - r) * middle.range_sum(r - ((r - l + 1) - m) + 1,r);
			sum2 += ((r - l + 1) - m + 1) * middle.range_sum(l + ((r - l + 1) - m),r - ((r - l + 1) - m));
			cout<<sum1 + sum2 + sum3<<'\n';
		}
	}
}
