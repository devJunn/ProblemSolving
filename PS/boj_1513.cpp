// N, M 이 15이하인 경우는 완전탐색으로 시도해볼 수 있음
//#include <iostream>
//#define MAX 1000007
//
//using namespace std;
//
//int N, M, C;
//int board[51][51];
//int counts[51];
//const int dys[] = { 1, 0 };
//const int dxs[] = { 0, 1 };
//
//void run(int y=1, int x=1, int prevC=0, int length=0) {
//	if (y == N && x == M) {
//		++counts[length];
//		counts[length] %= MAX;
//		return;
//	}
//	for (int d = 0; d < 2; ++d) {
//		int ny = y + dys[d];
//		int nx = x + dxs[d];
//		if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
//		if (board[ny][nx] == -1) continue;
//		if (board[ny][nx]) {
//			if (board[ny][nx] > prevC) {
//				int tmp = board[ny][nx];
//				board[ny][nx] = -1;
//				run(ny, nx, tmp, length + 1);
//				board[ny][nx] = tmp;
//			}
//		}
//		else {
//			board[ny][nx] = -1;
//			run(ny, nx, prevC, length);
//			board[ny][nx] = 0;
//		}
//	}
//}
//
//int main() {
//	cin >> N >> M >> C;
//	for (int i = 1; i <= C; ++i) {
//		int r, c;
//		cin >> r >> c;
//		board[r][c] = i;
//	}
//	run(1, 1, board[1][1], 0);
//	for (int i = 0; i <= C; ++i) cout << counts[i] << " ";
//}

// DP를 이용한 풀이
#include <iostream>
#include <string.h>
#define MOD 1000007

using namespace std;

int N, M, C;
int board[51][51];
int dp[51][51][51][51];

int solution(int y, int x, int prevC, int cnt) {
	if (y <= 0 || y > N || x <= 0 || x > M) return 0;
	if (y == N && x == M) {
		if (board[N][M] && board[N][M] > prevC && cnt == 1) return 1;
		if (board[N][M] == 0 && cnt == 0) return 1;
	}
	int& ret = dp[y][x][prevC][cnt];
	if (ret != -1) return ret;
	if (board[y][x] && board[y][x] > prevC && cnt >= 1) {
		ret = (solution(y+1, x, board[y][x], cnt-1) + solution(y, x+1, board[y][x], cnt-1))%MOD;
	}
	else if (board[y][x] == 0) {
		ret = (solution(y+1, x, prevC, cnt) + solution(y, x+1, prevC, cnt))%MOD;
	}
	else {
		ret = 0;
	}
	return ret;
}
int main() {
	memset(dp, -1, sizeof(dp));
	cin >> N >> M >> C;
	for (int i = 1; i <= C; ++i) {
		int y, x;
		cin >> y >> x;
		board[y][x] = i;
	}
	for (int cnt = 0; cnt <= C; ++cnt) cout << solution(1, 1, 0, cnt) << " ";
}