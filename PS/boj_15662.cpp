#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int T, K;
int state[1001][8];

void rotate(int arr[], int d) {
	if (d == 1) {
		int tmp = arr[7];
		for (int i = 6; i > -1; --i) arr[i+1] = arr[i];
		arr[0] = tmp;
	}
	else {
		int tmp = arr[0];
		for (int i = 1; i < 8; ++i) arr[i - 1] = arr[i];
		arr[7] = tmp;
	}
}

void run(int number, int direction, int (& visited)[1001], int tmp[1001][8]) {
	rotate(state[number], direction);
	visited[number] = 1;
	if (number + 1 <= T && tmp[number][2] != tmp[number+1][6] && visited[number + 1] == 0) run(number + 1, -direction, visited, tmp);
	if (number - 1 >= 1 && tmp[number - 1][2] != tmp[number][6] && visited[number - 1] == 0) run(number - 1, -direction, visited, tmp);
}

int main() {
	cin >> T;
	for (int i = 1; i <= T; ++i) {
		string row;
		cin >> row;
		for (int j = 0; j < 8; ++j) {
			state[i][j] = row[j] - '0';
		}
	}
	cin >> K;
	for (int t = 1; t <= K; ++t) {
		int number, direction;
		cin >> number >> direction;
		int tmp[1001][8];
		memcpy(tmp, state, sizeof(tmp));
		int visited[1001];
		memset(visited, 0, sizeof(visited));
		run(number, direction, visited, tmp);
	}
	int answer = 0;
	for (int i = 1; i <= T; ++i) {
		if (state[i][0] == 1) answer++;
	}
	cout << answer << '\n';
}