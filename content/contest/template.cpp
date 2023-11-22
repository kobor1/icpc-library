#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define FOR(i, b, e) for(int i = (b); i < (e); i++)
#define sz(x) ((int)size(x))
#define all(x) begin(x), end(x)
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define st first
#define nd second
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

auto &operator<<(auto &o, pair<auto, auto> p) {
	return o << "(" << p.st << ", " << p.nd << ")"; }
auto operator<<(auto &o, auto x)->decltype(end(x), o) {
	o << "{"; int i=0; for(auto e: x) o << ", " + 2*!i++ << e;
	return o << "}"; }
#ifdef LOCAL
#define deb(x...) cerr << "[" #x "]: ", [](auto...$) { \
					((cerr << $ << "; "),...) << endl; }(x)
#else
#define deb(...)
#endif

void solve() {
	
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int tt = 1;
	// cin >> tt;
	FOR(te, 0, tt) solve();
	return 0;
}
