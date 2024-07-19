/**
 * Author: kobor
 * Date: 2024-07-18
 * Description:
 * Source: own work
 */
#pragma GCC optimize("O3")
#include "bits/stdc++.h"	/** keep-include */
using namespace std;

#define rep(i, b, e) for(int i = (b); i <= (e); i++)
#define per(i, b, e) for(int i = (e); i >= (b); i--)
#define FOR(i, b, e) rep(i, b, (e) - 1)
#define SZ(x) int(x.size())
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

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

void solve() { }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tt = 1;
	// cin >> tt;
	FOR(te, 0, tt) solve();
	return 0;
}
