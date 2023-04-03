#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		v.push_back(x);
	}
	int tgt;
	cin >> tgt;
	sort(v.begin(), v.end(), less<int>());
	long long ret = 0;
	if (v.size() > 1) {
		int right = v.size() - 1;
		for (int left = 0; left < N; ++left) {
			if (right <= left) break;
			while (left < right) {
				int sum = v[left] + v[right];
				if (sum > tgt) {
					--right;
				}
				else {
					if (sum == tgt) ++ret;
					break;
				}
			}
		}
	}
	cout << ret << '\n';
}