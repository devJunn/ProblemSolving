#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N;
int arr[1001];
int cnt[1001];
int prevStep[1001];
int answer;
int lastIdx;

int main() {
	memset(prevStep, -1, sizeof(prevStep));
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}
	for (int i = 0; i < N; ++i) {
		int maxCnt = 0;
		for (int j = 0; j < i; ++j) {
			if (arr[j] < arr[i] && maxCnt < cnt[j]) {
				maxCnt = cnt[j];
				prevStep[i] = j;
			}
		}
		cnt[i] = maxCnt + 1;
		if (answer < cnt[i]) {
			answer = cnt[i];
			lastIdx = i;
		}
	}
	cout << answer << '\n';
	vector<int> lis;
	while (1) {
		lis.push_back(arr[lastIdx]);
		lastIdx = prevStep[lastIdx];
		if (lastIdx == -1) break;
	}
	for (int i = answer - 1; i >= 0; --i) cout << lis[i] << ' ';
}
