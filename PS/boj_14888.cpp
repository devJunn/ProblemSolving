#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> nums;
int n_ops[4];
int max_val = INT32_MIN;
int min_val = INT32_MAX;

int calc(int a, int b, int c)
{
	switch (c)
	{
	case 0:
		return a + b;
	case 1:
		return a - b;
	case 2:
		return a * b;
	case 3:
		if (a < 0) return -(-a / b);
		return a / b;
	}
}

void dfs(int step, vector<int>& state)
{
	if (step == N - 1)
	{
		int ret = nums[0];
		for (int i = 0; i < N - 1; i++)
		{
			ret = calc(ret, nums[i + 1], state[i]);
		}
		max_val = max(max_val, ret);
		min_val = min(min_val, ret);
	}

	for (int i = 0; i < 4; i++)
	{
		if (n_ops[i] == 0) continue;
		n_ops[i] -= 1;
		state.push_back(i);
		dfs(step + 1, state);
		state.pop_back();
		n_ops[i] += 1;
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int x = 0;
		cin >> x;
		nums.push_back(x);
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> n_ops[i];
	}
	vector<int> state;
	dfs(0, state);
	cout << max_val << '\n';
	cout << min_val << '\n';
}