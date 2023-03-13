#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int dys[] = { -1, 1, 0, 0 };
const int dxs[] = { 0, 0, -1, 1 };
int R, C, K;
char board[6][6];
bool visited[6][6];

int dfs(int y, int x, int cnt)
{
	if (y == 0 && x == C - 1)
	{
		if (cnt == K) return 1;
		return 0;
	}

	int ret = 0;

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dys[i];
		int nx = x + dxs[i];
		if (ny < 0 || ny >= R || nx < 0 || nx >= C || board[ny][nx] == 'T') continue;
		if (visited[ny][nx]) continue;
		visited[ny][nx] = true;
		ret += dfs(ny, nx, cnt + 1);
		visited[ny][nx] = false;
	}

	return ret;
}

int main()
{	
	memset(visited, false, sizeof(visited));
	cin >> R >> C >> K;
	for (int i = 0; i < R; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < C; j++) board[i][j] = s[j];
	}

	int start_y = R - 1;
	int start_x = 0;
	visited[start_y][start_x] = true;
	cout << dfs(start_y, start_x, 1);
}