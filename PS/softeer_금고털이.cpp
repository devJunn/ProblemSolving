#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int W, N;
vector<pair<int, int>> v;

bool compare(pair<int, int> A, pair<int, int> B) {
	if (A.second == B.second) return A.first < B.first;
	return A.second > B.second;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> W >> N;
	for (int i = 1; i <= N; ++i) {
		int m, p;
		cin >> m >> p;
		v.push_back({ m, p });
	}
	sort(v.begin(), v.end(), compare);
	int answer = 0;
	int weight = 0;
	for (int i = 0; i < N; ++i) {
		if (weight + v[i].first > W) {
			answer += (W - weight) * v[i].second;
			weight = W;
			break;
		}
		answer += v[i].first * v[i].second;
		weight += v[i].first;
	}
	cout << answer;
}