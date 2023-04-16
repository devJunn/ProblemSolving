#include <iostream>

using namespace std;

int N;
int costs[21];
int returns[21];
int dp[21][101];
int answer;

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> costs[i];
	for (int i = 0; i < N; ++i) cin >> returns[i];
	dp[0][100] = 0;
	if (costs[0] < 100) dp[0][100 - costs[0]] = returns[0];
	for (int t = 1; t < N; ++t) {
		for (int power = 1; power <= 100; ++power) {
			if (power + costs[t] <= 100) dp[t][power] = max(dp[t - 1][power], dp[t - 1][power + costs[t]] + returns[t]);
			else dp[t][power] = dp[t - 1][power];
		}
	}
	for (int power = 1; power <= 100; ++power) {
		answer = max(answer, dp[N - 1][power]);
	}
	cout << answer << '\n';
}