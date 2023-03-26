#include <iostream>
#include <queue>

using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		pq.push({ x, y });
	}
	int answer = 0, x = 0, y = 0;
	x = pq.top().first;
	y = pq.top().second;
	answer = y - x;
	pq.pop();
	for (int i = 1; i < n; i++)
	{
		if (pq.top().first <= y)
		{
			if (pq.top().second > y)
			{
				answer += pq.top().second - y;
				y = pq.top().second;
			}
		}
		else
		{
			x = pq.top().first;
			y = pq.top().second;
			answer += y - x;
		}
		pq.pop();
	}
	cout << answer << '\n';
}