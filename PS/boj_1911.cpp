#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> v;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N, L;
	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		int start = 0, end = 0;
		cin >> start >> end;
		v.push_back({ start, end });
	}
	sort(v.begin(), v.end(), less < pair<int, int>>());
	int curr = 0, answer=0, cnt=0;
	for (int i = 0; i < N; i++)
	{
		if (curr >= v[i].second) continue;

		if (v[i].first >= curr)
		{
			cnt = (v[i].second - v[i].first) / L + ((v[i].second - v[i].first) % L ? 1 : 0);
			curr = v[i].first + cnt * L;
		}
		else
		{
			cnt = (v[i].second - curr) / L + ((v[i].second - curr) % L ? 1 : 0);
			curr = curr + cnt * L;
		}
		answer += cnt;
	}
	cout << answer << '\n';
}