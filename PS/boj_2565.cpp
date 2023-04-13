#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, int>> v;
int arr[101];
int len;

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int x, y;
		cin >> x >> y;
		v.push_back({ x, y });
	}
	sort(v.begin(), v.end(), less<pair<int, int>>());
	for (int i = 0; i < N; ++i) {
		int* lb = lower_bound(arr, arr + len, v[i].second);
		if (*lb == 0) {
			*lb = v[i].second;
			len++;
		}
		else *lb = v[i].second;
	}
	cout << N - len << '\n';
}