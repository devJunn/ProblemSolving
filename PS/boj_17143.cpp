#include <iostream>
#include <string.h>

using namespace std;

struct Shark {
	int y;
	int x;
	int s;
	int d;
	int z;
	int death;
};

int R, C, M;
Shark sharks[10001];
int board[100][100];
int tmp[100][100];
int answer;
const int dys[] = { -1, 1, 0, 0 };
const int dxs[] = { 0, 0, 1, -1 };

void catchShark (int t) {
	for (int y = 0; y < R; ++y) {
		if (board[y][t]) {
			int sharkNumber = board[y][t];
			answer += sharks[sharkNumber].z;
			sharks[sharkNumber].death = 1;
			break;
		}
	}
}

void moveShark(int sharkNumber) {
	int y = sharks[sharkNumber].y;
	int x = sharks[sharkNumber].x;
	int s = sharks[sharkNumber].s;
	int d = sharks[sharkNumber].d;
	int z = sharks[sharkNumber].z;

	int ny = y + s * dys[d];
	int nx = x + s * dxs[d];
	while (ny < 0 || ny >= R || nx < 0 || nx >= C) {
		if (d == 0) {
			ny = 0;
			s -= y;
		}
		else if (d == 1) {
			ny = R - 1;
			s -= (R - 1 - y);
		}
		else if (d == 2) {
			nx = C - 1;
			s -= (C - 1 - x);
		}
		else {
			nx = 0;
			s -= x;
		}
		d ^= 1;
		y = ny;
		x = nx;
		ny += s * dys[d];
		nx += s * dxs[d];
	}

	sharks[sharkNumber].y = ny;
	sharks[sharkNumber].x = nx;
	sharks[sharkNumber].d = d;

	if (tmp[ny][nx]) {
		if (sharks[tmp[ny][nx]].z < z) {
			sharks[tmp[ny][nx]].death = 1;
			tmp[ny][nx] = sharkNumber;
		}
		else {
			sharks[sharkNumber].death = 1;
		}
	}
	else {
		tmp[ny][nx] = sharkNumber;
	}
}

int main() {
	cin >> R >> C >> M;
	for (int i = 1; i <= M; ++i) {
		int y, x, s, d, z;
		cin >> y >> x >> s >> d >> z;
		if (d < 3) sharks[i] = {y-1, x-1, s%(2*(R-1)), d-1, z};
		else sharks[i] = {y-1, x-1, s%(2*(C-1)), d-1, z};
		board[y - 1][x - 1] = i;
	}
	
	for (int t = 0; t < C; ++t) {
		// 낚시왕이 있는 열에 있는 상어 중에서 땅과 가장 가까운 상어를 잡는다.
		catchShark (t);

		// 상어가 이동한다.
		memset(tmp, 0, sizeof(tmp));
		for (int i = 1; i <= M; ++i) {
			if (sharks[i].death) continue;
			moveShark(i);
		}
		memcpy(board, tmp, sizeof(board));
	}
	cout << answer << '\n';
}