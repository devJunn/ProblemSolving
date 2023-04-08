#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int T, N, K, ret, answer;
int board[8][8];
const int dys[] = { -1, 0, 1, 0 };
const int dxs[] = { 0, 1, 0, -1 };
vector<pair<int, int>> tops;

vector<pair<int, int>> getTops() {
	int top_h = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			top_h = max(top_h, board[i][j]);
		}
	}
	vector<pair<int, int>> tops;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (board[i][j] == top_h) tops.push_back({ i, j });
		}
	}
	return tops;
}

bool check(int y, int x) {
	int ny, nx;
	for (int d = 0; d < 4; ++d) {
		ny = y + dys[d];
		nx = x + dxs[d];
		if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
		if (board[ny][nx] < board[y][x]) return true; // 등산로 조성을 계속 할 수 있음
	}
	return false;
}

int getMaxLength(int y, int x, int len) {
	if (!check(y, x)) {
		ret = max(ret, len);
		return ret;
	}
	int ny, nx;
	for (int d = 0; d < 4; ++d) {
		ny = y + dys[d];
		nx = x + dxs[d];
		if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
		if (board[ny][nx] < board[y][x]) {
			getMaxLength(ny, nx, len + 1);
		}
	}
	return ret;
}

int main() {
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		memset(board, 0, sizeof(board));
		cin >> N >> K;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> board[i][j];
			}
		}

		tops = getTops();
		for (auto top : tops) {
			answer = max(answer, getMaxLength(top.first, top.second, 1));
		}

		for (auto top : tops) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (top.first == i && top.second == j) continue;
					for (int k = 1; k <= K; ++k) {
						board[i][j] -= k;
						answer = max(answer, getMaxLength(top.first, top.second, 1));
						board[i][j] += k;
					}
				}
			}
		}

		cout << "#" << tc << " " << answer << "\n";
		ret = 0;
		answer = 0;
	}
}