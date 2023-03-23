#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int K, V, E;
vector<int> graph[20001];
int state[20001];
bool flag;

void check(int curr)
{
	if (!flag) return;

	for (int next : graph[curr])
	{
		if (state[next] == -1)
		{
			state[next] = (state[curr] + 1) % 2;
			check(next);
		}
		else
		{
			if (state[next] == state[curr])
			{
				flag = false;
				return;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> K;
	for (int k = 0; k < K; k++)
	{
		cin >> V >> E;
		memset(graph, {}, sizeof(graph));
		memset(state, -1, sizeof(state));
		for (int i = 0; i < E; i++)
		{
			int from, to;
			cin >> from >> to;
			graph[from].push_back(to);
			graph[to].push_back(from);
		}
		flag = true;
		for (int curr = 1; curr <= V; curr++)
		{
			if (state[curr] != -1) continue;
			state[curr] = 0;
			check(curr);
		}
		flag ? cout << "YES\n" : cout << "NO\n";
	}
}