#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int value;
	vector<int> next;
};

vector<Node> board;

void init() {
	board.push_back({ 0 });
	for (int i = 1; i <= 20; ++i) {
		board.push_back({ 2 * i });
		board[i - 1].next.push_back(i);
	}
	board.push_back({ 0 });
	board[20].next.push_back(21);
	for (int x : {13, 16, 19, 22, 24, 28, 27, 26, 25, 30, 35}) board.push_back({x});
	board[5].next.push_back(22);
	board[10].next.push_back(25);
	board[15].next.push_back(27);
	board[22].next.push_back(23);
	board[23].next.push_back(24);
	board[24].next.push_back(30);
	board[25].next.push_back(26);
	board[26].next.push_back(30);
	board[27].next.push_back(28);
	board[28].next.push_back(29);
	board[29].next.push_back(30);
	board[30].next.push_back(31);
	board[31].next.push_back(32);
	board[32].next.push_back(20);
}

int horses[4];
int answer;
int dices[10];

bool check(int i, int move) {
	int curr = horses[i];
	if (curr == 5 || curr == 10 || curr == 15) {
		curr = board[curr].next[1];
		for (int j = 1; j < move; ++j) {
			curr = board[curr].next[0];
			if (curr == 21) return true;
		}
		for (int j = 0; j < 4; ++j) {
			if (i == j) continue;
			if (curr == horses[j]) return false;
		}
	}
	else {
		for (int j = 0; j < move; ++j) {
			curr = board[curr].next[0];
			if (curr == 21) return true;
		}
		for (int j = 0; j < 4; ++j) {
			if (i == j) continue;
			if (curr == horses[j]) return false;
		}
	}
	return true;
}

void run(int step=0, int result=0) {
	if (step == 10) {
		answer = max(answer, result);
		return;
	}
	for (int i = 0; i < 4; ++i) {
		int curr = horses[i];
		if (curr == 21) continue;
		int dice = dices[step];
		if (!check(i, dice)) continue;
		if (curr == 5 || curr == 10 || curr == 15) {
			horses[i] = board[horses[i]].next[1];
			for (int j = 1; j < dice; ++j) {
				horses[i] = board[horses[i]].next[0];
				if (horses[i] == 21) break;
			}
		}
		else {
			for (int j = 0; j < dice; ++j) {
				horses[i] = board[horses[i]].next[0];
				if (horses[i] == 21) break;
			}
		}
		run(step + 1, result + board[horses[i]].value);
		horses[i] = curr;
	}
}

int main() {
	init();
	for (int i = 0; i < 10; ++i) cin >> dices[i];
	run();
	cout << answer << '\n';
}