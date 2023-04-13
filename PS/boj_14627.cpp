#include <iostream>

using namespace std;

int S, C;
int arr[1000001];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> S >> C;
	int left = 1;
	int right = 1;
	for (int i = 0; i < S; ++i) {
		cin >> arr[i];
		right = max(right, arr[i]);
	}
	int ret = 0;
	while (left <= right) {
		int mid = (left + right) / 2;
		int n = 0;
		for (int i = 0; i < S; ++i) {
			n += arr[i] / mid;
		}
		if (n >= C) {
			ret = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	long long answer = 0;
	int remain = -C;
	for (int i = 0; i < S; ++i) {
		answer += (arr[i] % ret);
		remain += (arr[i] / ret);
	}
	answer += (remain * ret);
	cout << answer << '\n';
}