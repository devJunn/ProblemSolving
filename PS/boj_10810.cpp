#include <iostream>

using namespace std;

int bucket[101];

void push_ball(int i, int j, int k)
{
	for (int curr = i; curr <= j; curr++)
	{
		bucket[curr] = k;
	}

}
int main()
{
	int N, M;
	cin >> N >> M;
	for (int t = 1; t <= M; t++)
	{
		int i, j, k;
		cin >> i >> j >> k;
		push_ball(i, j, k);
	}
	for (int i = 1; i <= N; i++)
	{
		cout << bucket[i] << ' ';
	}
}