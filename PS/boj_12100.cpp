#include <iostream>
#include <string.h>

using namespace std;

int N, answer;

struct Board {
	int arr[21][21];
	void _rotate() {
		// 시계방향으로 90도 회전
		int tmp[21][21];
		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < N; ++x) {
				tmp[y][x] = arr[N - 1 - x][y];
			}
		}
		memcpy(arr, tmp, sizeof(tmp));
	}
	void _move() {
		int tmp[21][21];
		for (int y = 0; y < N; ++y) {
			int idx = -1, flag = 0;
			for (int x = 0; x < N; ++x) {
				if (arr[y][x] == 0) continue;
				if (flag && arr[y][x] == tmp[y][idx]) tmp[y][idx] *= 2, flag = 0;
				else tmp[y][++idx] = arr[y][x], flag = 1;
			}
			for (int x = idx + 1; x < N; ++x) {
				tmp[y][x] = 0;
			}
		}
		memcpy(arr, tmp, sizeof(tmp));
	}

	void _getMax() {
		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < N; ++x) {
				answer = max(answer, arr[y][x]);
			}
		}
	}

	void _print() {
		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < N; ++x) {
				cout << arr[y][x] << ' ';
			}
			cout << '\n';
		}
	}
};

void run(Board board, int step = 1) {
	if (step > 5) {
		board._getMax();
		return;
	}
	for (int d = 0; d < 4; ++d) {
		Board newBoard = board;
		newBoard._move();
		run(newBoard, step+1);
		board._rotate();
	}
	return;
}

int main() {
	cin >> N;
	Board board;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			cin >> board.arr[y][x];
		}
	}
	run(board);
	cout << answer << '\n';
}