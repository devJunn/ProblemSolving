#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

struct Player
{
	int y;
	int x;
	int d;
	int s;
	int gun;

	bool operator<(const Player& other)
	{
		if (s + gun == other.s + other.gun)
		{
			return s < other.s;
		}
		return s + gun < other.s + other.gun;
	}
};

const int dys[] = { -1, 0, 1, 0 };
const int dxs[] = { 0, 1, 0, -1 };
int n, m, k;
vector<int> board[21][21];
Player players[31];
int state[21][21];
int points[31];

void move(int p_idx)
{
	Player &player = players[p_idx];
	int ny = player.y + dys[player.d];
	int nx = player.x + dxs[player.d];
	if (ny < 0 || ny >= n || nx < 0 || nx >= n)
	{
		player.d = (player.d + 2) % 4;
	}
	ny = player.y + dys[player.d];
	nx = player.x + dxs[player.d];
	state[player.y][player.x] = -1;
	player.y = ny;
	player.x = nx;
}

void simulation()
{
	for (int p_idx = 0; p_idx < m; p_idx++)
	{
		move(p_idx);
		Player &player = players[p_idx];
		if (state[player.y][player.x] == -1)
		{
			// 이동한 방향에 플레이어가 없는 경우
			if (!board[player.y][player.x].empty())
			{
				sort(board[player.y][player.x].begin(), board[player.y][player.x].end(), less<int>());
				if (player.gun < board[player.y][player.x].back())
				{
					int tmp = player.gun;
					player.gun = board[player.y][player.x].back();
					board[player.y][player.x].pop_back();
					if (tmp > 0) board[player.y][player.x].push_back(tmp);
				}
			}
			state[player.y][player.x] = p_idx;
		}
		else
		{
			// 이동한 방향에 플레이어가 있는 경우
			Player &other = players[state[player.y][player.x]];
			if (player < other)
			{
				// 현재 플레이어가 진 경우
				points[state[other.y][other.x]] += (other.s + other.gun - player.s - player.gun);

				if (player.gun > 0) board[other.y][other.x].push_back(player.gun);
				player.gun = 0;
				for (int i = 0; i < 4; i++)
				{
					int nd = (player.d + i) % 4;
					int ny = player.y + dys[nd];
					int nx = player.x + dxs[nd];
					if (ny < 0 || ny >= n || nx < 0 || nx >= n || state[ny][nx] != -1) continue;
					player.y = ny;
					player.x = nx;
					player.d = nd;
					if (!board[player.y][player.x].empty())
					{
						sort(board[player.y][player.x].begin(), board[player.y][player.x].end(), less<int>());
						player.gun = board[player.y][player.x].back();
						board[player.y][player.x].pop_back();
					}
					state[player.y][player.x] = p_idx;
					break;
				}
				
				if (!board[other.y][other.x].empty())
				{
					sort(board[other.y][other.x].begin(), board[other.y][other.x].end(), less<int>());
					if (other.gun < board[other.y][other.x].back())
					{
						int tmp = other.gun;
						other.gun = board[other.y][other.x].back();
						board[other.y][other.x].pop_back();
						if (tmp > 0) board[other.y][other.x].push_back(tmp);
					}
				}
			}
			else
			{
				// 현재 플레이어가 이긴 경우
				points[p_idx] += (player.s + player.gun - other.s - other.gun);

				int other_idx = state[player.y][player.x];
				state[player.y][player.x] = p_idx;
				if (other.gun > 0) board[other.y][other.x].push_back(other.gun);
				other.gun = 0;
				for (int i = 0; i < 4; i++)
				{
					int nd = (other.d + i) % 4;
					int ny = other.y + dys[nd];
					int nx = other.x + dxs[nd];
					if (ny < 0 || ny >= n || nx < 0 || nx >= n || state[ny][nx] != -1) continue;
					other.y = ny;
					other.x = nx;
					other.d = nd;
					if (!board[other.y][other.x].empty())
					{
						sort(board[other.y][other.x].begin(), board[other.y][other.x].end(), less<int>());
						other.gun = board[other.y][other.x].back();
						board[other.y][other.x].pop_back();
					}
					state[other.y][other.x] = other_idx;
					break;
				}

				if (!board[player.y][player.x].empty())
				{
					sort(board[player.y][player.x].begin(), board[player.y][player.x].end(), less<int>());
					if (player.gun < board[player.y][player.x].back())
					{
						int tmp = player.gun;
						player.gun = board[player.y][player.x].back();
						board[player.y][player.x].pop_back();
						if (tmp > 0) board[player.y][player.x].push_back(tmp);
					}
				}
			}
		}
	}
}

int main()
{
	memset(state, -1, sizeof(state));
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int g_atk;
			cin >> g_atk;
			if (g_atk > 0) board[i][j].push_back(g_atk);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int y, x, d, s;
		cin >> y >> x >> d >> s;
		players[i] = Player{ y-1, x-1, d, s };
		state[y-1][x-1] = i;
	}

	for (int round = 0; round < k; round++)
	{
		simulation();
	}
	for (int i = 0; i < m; i++)
	{
		cout << points[i] << " ";
	}
}