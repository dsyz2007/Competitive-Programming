#include <bits/stdc++.h>
#include "quality.h"
using namespace std;
using ll = long long;
#define MAXN (3005)
ll A[MAXN][MAXN], dp[MAXN][MAXN];
int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	ll high = R * C + 5;
	ll low = 0;
	while(high - low > 1){
		ll mid = (high + low) / 2;
		memset(A,0,sizeof(A));
		for(ll i = 1;i <= R;i++){ //arrays A and dp are 1-indexed, Q is 0-indexed
			for(ll j = 1;j <= C;j++){
				if(Q[i - 1][j - 1] <= mid){
					A[i][j] = 1;
				}
			}
		}
		memset(dp,0,sizeof(dp));
		for(ll i = 1;i <= R;i++){
			for(ll j = 1;j <= C;j++){
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + A[i][j];
			}
		}
		ll maximum = 0;
		ll medianindex = ((H * W) + 1) / 2; //1-indexed
		for(ll i = 1;i <= R - H + 1;i++){
			for(ll j = 1;j <= C - W + 1;j++){
				ll b = i + H - 1;
				ll c = j + W - 1;
				ll sum = dp[b][c] - dp[i - 1][c] - dp[b][j - 1] + dp[i - 1][j - 1];
				maximum = max(maximum,sum);
			}
		}
		if(maximum >= medianindex){
			high = mid;	
		}else{
			low = mid;
		}
	}
	return high;
}
