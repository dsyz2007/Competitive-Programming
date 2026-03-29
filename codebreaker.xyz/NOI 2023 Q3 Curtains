#include <bits/stdc++.h>
using namespace std;
using ll = int;
#define MAXN (1000005)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
int readInt() 
{
  int x = 0; 
  char ch=getchar_unlocked(); 
  bool s=1;
  while(ch<'0'||ch>'9'){if(ch=='-')s=0;ch=getchar_unlocked();}
  while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar_unlocked();}
  return s?x:-x;
}
struct node{
	int s,e,m,v,lazyadd;
	node *l,*r;
	node(int _s,int _e){
		s = _s;
		e = _e;
		m = (s + e) >> 1;
		v = 1e9;
		lazyadd = 1e9;
		if(s != e){
			l = new node(s,m);
			r = new node(m + 1,e);
		}
	}
	int value(){
		if(s == e){
			v = min(v,lazyadd);
			return v;
		}
		v = min(v,lazyadd);
		r->lazyadd = min(r -> lazyadd,lazyadd);
		l->lazyadd = min(l -> lazyadd,lazyadd);
		return v;
	}
	void update(int x,int y,int val){
		if(s == x && e == y) lazyadd = min(lazyadd,val);
		else{
			if(x > m) r -> update(x,y,val);
			else if(y <= m) l -> update(x,y,val);
			else l -> update(x,m,val), r -> update(m + 1,y,val);
			v = max(l->value(),r->value());
		}
	}
	int rmq(int x,int y){
		value();
		if(s == x && e == y) return value();
		if(x > m) return r -> rmq(x,y);
		if(y <= m) return l -> rmq(x,y);
		return max(l -> rmq(x,m),r -> rmq(m + 1,y)); 
	}
} *root;
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);
	ll N,M,Q;
	N = readInt(), M = readInt(), Q = readInt();
	root = new node(0,N);
	vector<pair<ll,ll> > curtain;
	for(ll i = 0;i < M;i++){
		ll S,E;
		S = readInt(), E = readInt();
		curtain.push_back({S,E});
	}
	vector<pair<pair<ll,ll>,ll> > queries;
	for(ll i = 0;i < Q;i++){
		ll L,R;
		L = readInt(), R = readInt();
		queries.push_back({{L,R},i});
	}
	sort(curtain.begin(),curtain.end());
	sort(queries.begin(),queries.end());
	bool ans[Q];
	memset(ans,0,sizeof(ans));
	ll leftmost = 1e9;
	for(ll i = queries.size() - 1;i >= 0;i--){
		ll L = queries[i].first.first;
		ll R = queries[i].first.second;
		ll index = queries[i].second;
		while(!curtain.empty() && curtain.back().first >= L){
			root -> update(curtain.back().first,curtain.back().second,curtain.back().second);
			leftmost = curtain.back().first;
			curtain.pop_back();
		}
		if(root -> rmq(L,R) == R && leftmost == L){
			ans[index] = 1;
		}
	}
	for(ll i = 0;i < Q;i++){
		if(ans[i]) cout<<"YES"<<'\n';
		else cout<<"NO"<<'\n';
	}
}
