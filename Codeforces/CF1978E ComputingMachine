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
		string olda, oldb;
		cin>>olda>>oldb;
		string A = olda, B = oldb;
		for(ll i = 2;i < N;i++){
			if(A[i - 2] == '0' && A[i] == '0'){
				B[i - 1] = '1';
			}
		}
		ll psum[N];
		ll cur = 0;
		for(ll i = 0;i < N;i++){
			if(A[i] == '1'){
				cur++;
			}else if(i >= 1 && i < N - 1){
				if(B[i - 1] == '1' && B[i + 1] == '1'){
					A[i] = '1';
					cur++;
				}
			}
			psum[i] = cur;
		}
		ll Q;
		cin>>Q;
		for(ll q = 0;q < Q;q++){
			ll l,r;
			cin>>l>>r;
			l--, r--;
			if(r - l + 1 <= 10){
				string aa = "", bb = "";
				for(ll i = l;i <= r;i++){
					aa += olda[i];
					bb += oldb[i];
				}
				ll nn = aa.size();
				for(ll i = 2;i < nn;i++){
					if(aa[i - 2] == '0' && aa[i] == '0'){
						bb[i - 1] = '1';
					}
				}
				ll ans = 0;
				for(ll i = 0;i < nn;i++){
					if(aa[i] == '1'){
						ans++;
					}else if(i >= 1 && i < nn - 1){
						if(bb[i - 1] == '1' && bb[i + 1] == '1'){
							ans++;
						}
					}
				}
				cout<<ans<<'\n';
			}else{
				ll ans = psum[r];
				if(l >= 1) ans -= psum[l - 1];
				if(olda[l] == '0' && A[l] == '1') ans--;
				if(oldb[l] == '0' && B[l] == '1' && olda[l + 1] == '0' && A[l + 1] == '1') ans--;
				
				if(olda[r] == '0' && A[r] == '1') ans--;
				if(oldb[r] == '0' && B[r] == '1' && olda[r - 1] == '0' && A[r - 1] == '1') ans--;
				cout<<ans<<'\n';
			}
		}
	}
}
