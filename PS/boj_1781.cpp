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
	int N;
	cin >> N;
	v.reserve(N);
	for (int i = 0; i < N; i++)
	{
		int deadline, num;
		cin >> deadline >> num;
		v.push_back({ deadline, num });
	}
	sort(v.begin(), v.end());
	int answer = 0;
	for (int i = 0; i < N; i++)
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