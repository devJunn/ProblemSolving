#include <iostream>
#include <string>

using namespace std;

int H, W;
char board[30][30];
const int dys[] = { -1, 0, 1, 0 };
const int dxs[] = { 0, 1, 0, -1 };
const char directions[] = { '^', '>', 'v', '<' };
int startY, startX, startD;
bool visited[30][30];
string path = "";

pair<int, int> check(int y, int x) {
	int cnt = 0;
	int direction = 0;
	for (int d = 0; d < 4; ++d) {
		int ny = y + dys[d];
		int nx = x + dxs[d];
		if (ny <= 0 || ny > H || nx <= 0 || nx > W) continue;
		if (board[ny][nx] == '#') {
			++cnt;
			direction = d;
		}
	}
	return { cnt, direction };
}

void getStartingPoint() {
	for (int y = 1; y <= H; ++y) {
		for (int x = 1; x <= W; ++x) {
			if (board[y][x] != '#') continue;
			pair<int, int> ret = check(y, x);
			if (ret.first == 1) {
				startY = y;
				startX = x;
				startD = ret.second;
				cout << startY << " " << startX << "\n";
				cout << directions[startD] << "\n";
				return;
			}
		}
	}
}

struct Pos {
	int y;
	int x;
	int d;
};

Pos getNext(int y, int x) {
	for (int d = 0; d < 4; ++d) {
		int ny = y + dys[d];
		int nx = x + dxs[d];
		if (ny <= 0 || ny > H || nx <= 0 || nx > W) continue;
		if (visited[ny][nx]) continue;
		if (board[ny][nx] == '#') return { ny, nx, d };
	}
	return { -1, -1, -1 };
}

void getPath() {
	int y = startY;
	int x = startX;
	int d = startD;
	visited[y][x] = true;
	while (1) {
		Pos nextPos = getNext(y, x);
		if (nextPos.y == -1) break;
		if (d == nextPos.d) {
			path += "A";
			for (int i = 0; i < 2; ++i) {
				y += dys[d];
				x += dxs[d];
				visited[y][x] = true;
			}
		}
		else {
			if (abs(d - nextPos.d) == 2) {
				path += "LL";
			}
			else if (nextPos.d == (d + 3) % 4) {
				path += "L";
			}
			else {
				path += "R";
			}
			d = nextPos.d;
		}
	}
	cout << path << "\n";
}

int main() {
	cin >> H >> W;
	for (int y = 1; y <= H; ++y) {
		string line;
		cin >> line;
		for (int x = 1; x <= W; ++x) board[y][x] = line[x-1];
	}
	getStartingPoint();
	getPath();
}
