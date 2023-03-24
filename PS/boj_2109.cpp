#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> v;
priority_queue<int, vector<int>, greater<int>> pq;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int d, p;
		cin >> p >> d;
		v.push_back({ d, p });
	}
	sort(v.begin(), v.end());
	int answer = 0;
	for (int i = 0; i < n; i++)
	{
		if (pq.size() >= v[i].first)
		{
			if (pq.top() < v[i].second)
			{
				answer -= pq.top();
				pq.pop();
				answer += v[i].second;
				pq.push(v[i].second);
			}
		}
		else
		{
			answer += v[i].second;
			pq.push(v[i].second);
		}
	}
	cout << answer << '\n';
}