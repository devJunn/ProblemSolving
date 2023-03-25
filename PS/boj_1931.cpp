#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> v;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin >> N;
	v.reserve(N);
	for (int i = 0; i < N; i++)
	{
		int start, end;
		cin >> start >> end;
		v.push_back({ end, start });
	}
	sort(v.begin(), v.end(), less<pair<int, int>>());
	int answer = 0;
	int last = 0;
	for (int i = 0; i < N; i++)
	{
		if (last <= v[i].second)
		{
			answer += 1;
			last = v[i].first;
		}
	}
	cout << answer << '\n';
}