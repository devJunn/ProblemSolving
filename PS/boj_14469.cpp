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
		int arrive, time;
		cin >> arrive >> time;
		v.push_back({ arrive, time });
	}
	sort(v.begin(), v.end(), less<pair<int, int>>());
	int answer = 0;
	for (int i = 0; i < N; i++)
	{
		answer = max(answer, v[i].first);
		answer += v[i].second;
	}
	cout << answer << '\n';
}