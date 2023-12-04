/**
 * Author: kobor
 * Date: 2023-12-04
 * License: CC0
 * Source: Anadi's github
 * Description: Finds minimum number of knight moves from (x,y) to (0,0) in non-negative infinite chessboard.
 * Time: O(1)
 * Status: not tested
 */
#pragma once

ll knightMoves(ll x, ll y) {
	ll cnt = max({(x + 1) / 2, (y + 1) / 2, (x + y + 2) / 3});
	while((cnt % 2) != (x + y) % 2) cnt++;
	if(x == 1 && !y) return 3;
	if(y == 1 && !x) return 3;
	if(x == y && x == 2) return 4;
	return cnt;
}
