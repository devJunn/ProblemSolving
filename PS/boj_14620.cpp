#include <iostream>

using namespace std;

const int K = 3;
const int dys[] = { 0, -1, 1, 0, 0 };
const int dxs[] = { 0, 0, 0, -1, 1 };
int N;
int board[11][11];
bool visited[11][11];
int answer = 10000;
int ret = 0;

bool check(int y, int x)
{
	for (int i = 0; i < 5; i++)
	{
		int ny = y + dys[i];
		int nx = x + dxs[i];
		if (visited[ny][nx]) return false;
	}
	return true;
}

void update(int y, int x)
{
	for (int i = 0; i < 5; i++)
	{
		int ny = y + dys[i];
		int nx = x + dxs[i];
		visited[ny][nx] = true;
		ret += board[ny][nx];
	}
}

void reset(int y, int x)
{
	for (int i = 0; i < 5; i++)
	{
		int ny = y + dys[i];
		int nx = x + dxs[i];
		visited[ny][nx] = false;
		ret -= board[ny][nx];
	}
}

int dfs(int cnt = 0)
{
	if (cnt == K)
	{
		return min(answer, ret);
	}

	for (int i = 1; i < N - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			if (!check(i, j)) continue;
			update(i, j);
			answer = dfs(cnt + 1);
			reset(i, j);
		}
	}
	return answer;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}
	cout << dfs();
}