#include <iostream>

using namespace std;

int N, H, M;
bool ladders[31][10];
int answer = 1000;

bool check()
{
	bool flag = true;
	for (int i = 1; i <= N; i++)
	{
		int curr = i;
		for (int j = 1; j <= H; j++)
		{
			if (curr - 1 > 0 && ladders[j][curr - 1]) curr = curr - 1;
			else if (curr < N && ladders[j][curr]) curr = curr + 1;
		}
		if (curr != i)
		{
			flag = false;
			break;
		}
	}
	return flag;
}

void dfs(int here = 1, int cnt = 0)
{
	if (cnt >= answer)
	{
		return;
	}

	if (check())
	{
		answer = min(answer, cnt);
		return;
	}
	else
	{
		if (cnt == 3) return;
	}

	for (int i = here; i <= H; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (ladders[i][j]) continue;
			if (j - 1 > 0 && ladders[i][j - 1]) continue;
			if (j + 1 < N && ladders[i][j + 1]) continue;
			ladders[i][j] = true;
			dfs(i, cnt + 1);
			ladders[i][j] = false;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++)
	{
		int y, x;
		cin >> y >> x;
		ladders[y][x] = true;
	}

	dfs();

	if (answer == 1000) answer = -1;
	cout << answer;
}