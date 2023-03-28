#include <iostream>
#include <vector>

using namespace std;

int N, curr;
int answer = INT32_MIN;
vector<int> v;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> N;
	v.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		int x = 0;
		cin >> x;
		v.push_back(x);
	}

	for (int i = 0; i < N; ++i)
	{
		curr += v[i];
		answer = max(answer, curr);
		if (curr < 0)
		{
			curr = 0;
		}
	}
	cout << answer << '\n';
}