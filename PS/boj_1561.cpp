#include <iostream>

using namespace std;

#define MAX 60000000005
int N, M;
int arr[10005];

int main() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		cin >> arr[i];
	}
	if (N <= M) cout << N << '\n';
	else {
		long long ret = 0;
		long long left = 0;
		long long right = MAX;
		while (left <= right) {
			long long mid = (left + right) / 2;
			long long temp = M;
			for (int i = 0; i < M; ++i) {
				temp += mid / arr[i];
			}
			if (temp >= N) {
				ret = mid;
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		long long temp = M;
		for (int i = 0; i < M; ++i) {
			temp += (ret - 1) / arr[i];
		}
		for (int i = 0; i < M; ++i) {
			if (ret % arr[i] == 0) ++temp;
			if (temp == N) {
				cout << i + 1 << '\n';
				break;
			}
		}
	}
}