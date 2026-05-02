#include <bits/stdc++.h>
#include "xylophone.h"
using namespace std;
using ll = long long;
#define MAXN (1000005)
 
void solve(int N) {
	ll low = 1;
	ll high = N + 1;
	while(high - low > 1){
		ll mid = (high + low) / 2;
		ll diff = query(mid,N);
		if(diff == N - 1){
			low = mid;
		}else{
			high = mid;
		}
	}
	ll posof1 = low;
	ll val[N + 1]; //pos of value i
	memset(val,-1,sizeof(val));
	val[1] = posof1;
	ll pos[N + 1]; //value of pos i
	memset(pos,-1,sizeof(pos));
	pos[posof1] = 1;
	for(ll i = posof1 + 1;i <= N;i++){ //all index are 1-indexed
		ll adjdiff = query(i - 1,i);
		if(pos[i - 1] - adjdiff < 1 || val[pos[i - 1] - adjdiff] != -1){
			pos[i] = pos[i - 1] + adjdiff;
			val[pos[i - 1] + adjdiff] = i;
		}else if(pos[i - 1] + adjdiff > N || val[pos[i - 1] + adjdiff] != -1){
			pos[i] = pos[i - 1] - adjdiff;
			val[pos[i - 1] - adjdiff] = i;
		}else{ //I can prove this is at least 2 spaces away from val 1
			ll diff = query(i - 2,i);
			ll I1 = pos[i - 1] - adjdiff;
			ll I2 = pos[i - 1] + adjdiff;
			if(diff == abs(pos[i - 1] - pos[i - 2])){
				assert(pos[i - 1] != pos[i - 2]);
				if(pos[i - 1] > pos[i - 2]){
					pos[i] = pos[i - 1] - adjdiff;
					val[pos[i - 1] - adjdiff] = i;
				}else{
					pos[i] = pos[i - 1] + adjdiff;
					val[pos[i - 1] + adjdiff] = i;
				}
			}else if(diff == max({I1,pos[i - 1],pos[i - 2]}) - min({I1,pos[i - 1],pos[i - 2]})){
              	assert(diff != 0);
				pos[i] = I1;
				val[I1] = i;
			}else if(diff == max({I2,pos[i - 1],pos[i - 2]}) - min({I2,pos[i - 1],pos[i - 2]})){
              	assert(diff != 0);
				pos[i] = I2;
				val[I2] = i;
			}
		}
	}
	
	for(ll i = posof1 - 1;i >= 1;i--){ //all index are 1-indexed
		ll adjdiff = query(i,i + 1);
		if(pos[i + 1] - adjdiff < 1 || val[pos[i + 1] - adjdiff] != -1){
			pos[i] = pos[i + 1] + adjdiff;
			val[pos[i + 1] + adjdiff] = i;
		}else if(pos[i + 1] + adjdiff > N || val[pos[i + 1] + adjdiff] != -1){
			pos[i] = pos[i + 1] - adjdiff;
			val[pos[i + 1] - adjdiff] = i;
		}else{ //I can prove this is at least 2 spaces away from val 1
			ll diff = query(i,i + 2);
			ll I1 = pos[i + 1] - adjdiff;
			ll I2 = pos[i + 1] + adjdiff;
			if(diff == abs(pos[i + 1] - pos[i + 2])){
				assert(pos[i + 1] != pos[i + 2]);
				if(pos[i + 1] > pos[i + 2]){
					pos[i] = pos[i + 1] - adjdiff;
					val[pos[i + 1] - adjdiff] = i;
				}else{
					pos[i] = pos[i + 1] + adjdiff;
					val[pos[i + 1] + adjdiff] = i;
				}
			}else if(diff == max({I1,pos[i + 1],pos[i + 2]}) - min({I1,pos[i + 1],pos[i + 2]})){
              	assert(diff != 0);
				pos[i] = I1;
				val[I1] = i;
			}else if(diff == max({I2,pos[i + 1],pos[i + 2]}) - min({I2,pos[i + 1],pos[i + 2]})){
              	assert(diff != 0);
				pos[i] = I2;
				val[I2] = i;
			}
		}
	}
	for(ll i = 1;i <= N;i++){
		answer(i,pos[i]);
	}
}
