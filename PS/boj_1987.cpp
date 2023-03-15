#include <iostream>

using namespace std;

const int dys[] = { -1, 1, 0, 0 };
const int dxs[] = { 0, 0, -1, 1 };
int R, C;
bool used[30];
char board[21][21];
int answer = 0;

void dfs(int y=0, int x=0, int cnt = 1)
{	
	answer = max(answer, cnt);

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dys[i];
		int nx = x + dxs[i];
		if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
		if (used[board[ny][nx] - 'A']) continue;
		used[board[ny][nx] - 'A'] = true;
		dfs(ny, nx, cnt + 1);
		used[board[ny][nx] - 'A'] = false;
	}
}

int main()
{
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> board[i][j];
		}
	}
	used[board[0][0] - 'A'] = true;
	dfs();
	cout << answer;
}