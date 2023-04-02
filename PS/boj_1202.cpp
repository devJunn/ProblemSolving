#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> jewerly;
vector<int> bag;
priority_queue<int, vector<int>, less<int>> pq;

int main()
{
	int N, K;
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		int m, v;
		cin >> m >> v;
		jewerly.push_back({ m, v });
	}
	for (int i = 0; i < K; ++i) {
		int c;
		cin >> c;
		bag.push_back(c);
	}
	sort(jewerly.begin(), jewerly.end(), greater<pair<int, int>>());
	sort(bag.begin(), bag.end(), less<int>());
	long long answer = 0;
	for (int i = 0; i < K; ++i) {
		while (jewerly.size()) {
			if (jewerly.back().first > bag[i]) break;
			pq.push(jewerly.back().second);
			jewerly.pop_back();
		}
		if (!pq.empty()) {
			answer += pq.top();
			pq.pop();
		}
	}
	cout << answer << '\n';
}