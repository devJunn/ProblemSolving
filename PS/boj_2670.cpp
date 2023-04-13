#include <stdio.h>
#include <iostream>

using namespace std;

int N;
double arr[10001];
double result[10001];
double answer;

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
		if (i == 0) result[i] = arr[i];
		else {
			(result[i - 1] > 1) ? result[i] = result[i - 1] * arr[i] : result[i] = arr[i];
		}
		answer = max(answer, result[i]);
	}
	printf("%.3f\n", answer);
}