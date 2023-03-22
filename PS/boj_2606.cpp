#include <iostream>
#include <vector>

using namespace std;

int answer = 0;
vector<int> NETWORK[101];
bool visited[101];

void dfs(int curr)
{
	for (int next : NETWORK[curr])
	{
		if (!visited[next])
		{
			visited[next] = true;
			answer += 1;
			dfs(next);
		}
	}

}

int main()
{
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		NETWORK[from].push_back(to);
		NETWORK[to].push_back(from);
	}
	visited[1] = true;
	dfs(1);
	cout << answer;
}