#include <iostream>
#include <vector>

using namespace std;

int N;
int S[20][20];
int answer = INT32_MAX;

int bit_count(int bits)
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (bits & (1 << i)) ++cnt;
	}
	return cnt;
}

int calc_diff(vector<int>& team1, vector<int>& team2)
{
	int stat1 = 0, stat2 = 0;
	for (int i = 0; i < N / 2; i++)
	{
		for (int j = i+1; j < N / 2; j++)
		{
			stat1 += (S[team1[i]][team1[j]] + S[team1[j]][team1[i]]);
			stat2 += (S[team2[i]][team2[j]] + S[team2[j]][team2[i]]);
		}
	}
	return abs(stat1 - stat2);
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> S[i][j];
		}
	}

	for (int i = 0; i < (1 << N); i++)
	{
		if (bit_count(i) != N / 2) continue;
		vector<int> team1, team2;
		for (int j = 0; j < N; j++)
		{
			if (i & (1 << j))
			{
				team1.push_back(j);
			}
			else
			{
				team2.push_back(j);
			}
		}
		answer = min(answer, calc_diff(team1, team2));
	}
	cout << answer << '\n';
}