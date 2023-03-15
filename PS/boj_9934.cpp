#include <iostream>

using namespace std;

int MAX;
int tree[1024];

void dfs(int curr=1)
{
	if (curr >= MAX) return;

	dfs(2 * curr);
	cin >> tree[curr];
	dfs(2 * curr + 1);
}

int main()
{
	int K;
	cin >> K;
	MAX = 1 << K;
	dfs();
	int curr = 1;
	for (int l = 0; l < K; l++)
	{
		for (int i = 0; i < 1 << l; i++)
		{
			cout << tree[curr] << ' ';
			curr++;
		}
		cout << '\n';
	}
}