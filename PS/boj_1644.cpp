#include <iostream>
#include <vector>

using namespace std;

bool isPrime[4000001];
vector<int> v;

int main()
{
	int n;
	cin >> n;
	for (int i = 2; i <= n; i++)
	{
		if (!isPrime[i])
		{
			for (int j = 2 * i; j <= n; j += i)
			{
				isPrime[j] = true;
			}
		}
	}
	for (int i = 2; i <= n; i++)
	{
		if (!isPrime[i])
			v.push_back(i);
	}
	int answer = 0, left = 0, right = 0, sum = 0;
	while (1)
	{
		if (sum == n)
		{
			++answer;
			sum -= v[left];
			++left;
		}
		else if (sum > n)
		{
			sum -= v[left];
			++left;
		}
		else
		{
			if (right >= v.size()) break;
			sum += v[right];
			++right;
		}
	}
	cout << answer << '\n';
}