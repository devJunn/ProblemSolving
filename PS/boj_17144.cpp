#include <iostream>
#include <string.h>

using namespace std;

const int dys[] = { -1, 0, 1, 0 };
const int dxs[] = { 0, 1, 0, -1 };
int dys1[] = {-1, 0, 1, 0 };
int dxs1[] = {0, 1, 0, -1};
int dys2[] = {1, 0, -1, 0};
int dxs2[] = {0, 1, 0, -1};
int R, C, T;
int board[51][51];
int cleaner_y1 = -1, cleaner_y2 = -1;

void run1() {
	int tmp[51][51];
	memset(tmp, 0, sizeof(tmp));
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			if (board[r][c] > 0) {
				tmp[r][c] += board[r][c];
				int spread = board[r][c] / 5;
				for (int d = 0; d < 4; ++d) {
					int nr = r + dys[d];
					int nc = c + dxs[d];
					if (nr < 0 || nr >= R || nc < 0 || nc >= C || board[nr][nc] == -1) continue;
					tmp[nr][nc] += spread;
					tmp[r][c] -= spread;
				}
			}
		}
	}
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			board[r][c] = tmp[r][c];
		}
	}
	board[cleaner_y1][0] = -1;
	board[cleaner_y2][0] = -1;
}

void run2(int sy, int sx, int state, int dys[], int dxs[]) {
	int y = sy, x = sx;
	int d = 0;
	if (state == 0) {
		while (true) {
			int ny = y + dys[d];
			int nx = x + dxs[d];
			if (ny < 0 || ny > sy || nx < 0 || nx >= C) {
				++d;
				ny = y + dys[d];
				nx = x + dxs[d];
			}
			if (ny == sy && nx == sx) board[y][x] = 0;
			else board[y][x] = board[ny][nx];
			y = ny, x = nx;
			if (y == sy && x == sx) break;
		}
		board[y][x] = -1;
	}
	else {
		while (true) {
			int ny = y + dys[d];
			int nx = x + dxs[d];
			if (ny < sy || ny >= R || nx < 0 || nx >= C) {
				++d;
				ny = y + dys[d];
				nx = x + dxs[d];
			}
			if (ny == sy && nx == sx) board[y][x] = 0;
			else board[y][x] = board[ny][nx];
			y = ny, x = nx;
			if (y == sy && x == sx) break;
		}
		board[y][x] = -1;
	}
}

int main() {
	cin >> R >> C >> T;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			cin >> board[r][c];
			if (board[r][c] == -1) {
				if (cleaner_y1 == -1) cleaner_y1 = r;
				else cleaner_y2 = r;
			}
		}
	}

	for (int t = 1; t <= T; ++t) {
		run1();
		run2(cleaner_y1, 0, 0, dys1, dxs1);
		run2(cleaner_y2, 0, 1, dys2, dxs2);
	}

	int ret = 2;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			ret += board[r][c];
		}
	}
	cout << ret << '\n';
}