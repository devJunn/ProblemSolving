#include <iostream>

using namespace std;

const int dys[] = { 0, -1, 0, 1 };
const int dxs[] = { 1, 0, -1, 0 };

int N;
int dragonCurves[4][1024];
int board[101][101];
int answer;

void init(int generation=0) {
	if (generation > 10) return;
	if (generation == 0) {
		for (int d = 0; d < 4; ++d) {
			dragonCurves[d][generation] = d;
		}
	}
	else {
		for (int d = 0; d < 4; ++d) {
			int idx = 1 << (generation - 1);
			for (int i = 0; i < idx; ++i) {
				dragonCurves[d][idx + i] = (dragonCurves[d][idx - i - 1] + 1) % 4;
			}
		}
	}
	init(generation + 1);
}

void update(int x, int y, int d, int g) {
	board[x][y] = 1;
	for (int i = 0; i < (1 << g); ++i) {
		y += dys[dragonCurves[d][i]];
		x += dxs[dragonCurves[d][i]];
		if (0 <= x && x <= 100 && 0 <= y && y <= 100) board[x][y] = 1;
	}
}

bool check(int x, int y) {
	int dys[] = { 0, 0,1,1};
	int dxs[] = { 0, 1,0,1 };
	for (int i = 0; i < 4; ++i) {
		if (board[x + dxs[i]][y + dys[i]] == 0) return false;
	}
	return true;
}

int main() {
	init();
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		update(x, y, d, g);
	}
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 100; ++y) {
			if (check(x, y)) ++answer;
		}
	}
	cout << answer;
}
