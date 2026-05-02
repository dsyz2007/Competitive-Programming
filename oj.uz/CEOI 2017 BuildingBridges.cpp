#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAXN (100005)
ll N;
ll H[MAXN], W[MAXN], psum[MAXN], dp[MAXN];
struct node {
	ll s,e,m;
	bool reset;
	pair<ll,ll> line;
	node *l, *r;
	node(ll _s,ll _e){
		s = _s;
		e = _e;
		m = (s + e) >> 1; //Note that m = (s + e) / 2 will not work
		line = {0,1e18};
		reset = 0;
		l = nullptr, r = nullptr;
	}
	ll f(pair<ll,ll> line,ll x){
		return line.first * x + line.second;
	}
	void update(pair<ll,ll> nval){
		value();
		bool lt = f(nval,s) < f(line,s);
		bool mid = f(nval,m) < f(line,m);
		if(mid) swap(nval,line);
		if(s == e) return;
		if(lt == mid){
			if(r == nullptr) r = new node(m + 1,e);
			r -> update(nval);
		}else{
			if(l == nullptr) l = new node(s,m);
			l -> update(nval);
		}
	}
	ll rmq(ll x){
		value();
		if(s == e) return f(line,x);		
		if(x > m){
			ll RR = 1e18; //make sure to calculate RR inside the “x > m” if statement, if you do it outside the if statement, you might TLE
			if(r != nullptr) RR = r -> rmq(x);
			return min(f(line,x),RR);
		}else{
			ll LL = 1e18; 
			if(l != nullptr) LL = l -> rmq(x);		
			return min(f(line,x),LL);
		}
	}
	void value() {
		//this value() function is generally for codeforces problems with multiple testcases
		//so need to reset for each testcase to save space
		if(!reset) return;
		line = {0,1e18};
		if(s != e){
			if(l != nullptr) l -> reset = 1;
			if(r != nullptr) r -> reset = 1;
		}
		reset = 0;
	}
} *lichao;
//this is the minimum y lichao tree
//for maximum lichao tree, need to change all the
//min() to max() and 1e18 to -1e18 and "<" to ">" in update function
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>N;
	lichao = new node(-1e9,1e9);
	for(ll i = 1;i <= N;i++){
		cin>>H[i];
	}
	for(ll i = 1;i <= N;i++){
		cin>>W[i];
	}
	for(ll i = 1;i <= N;i++){
		psum[i] = psum[i - 1] + W[i];
	}
	dp[1] = 0;
	lichao -> update({-2 * H[1],(H[1] * H[1]) - psum[1] + dp[1]});
	for(ll i = 2;i <= N;i++){
		dp[i] = (H[i] * H[i]) + psum[i - 1] + lichao -> rmq(H[i]);
		lichao -> update({-2 * H[i],(H[i] * H[i]) - psum[i] + dp[i]});
	}
	cout<<dp[N]<<'\n';
}
