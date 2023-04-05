#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
struct Item {
	int num;
	int cnt;
	int t;
};
vector<Item> v;
bool visited[101];

bool compare(Item a, Item b) {
	if (a.cnt == b.cnt) return a.t > b.t;
	return a.cnt > b.cnt;
}

void update(int t, int n) {
	if (visited[n]) {
		vector<Item> tmp;
		for (auto item : v) {
			if (item.num == n) tmp.push_back({ n, item.cnt + 1, item.t });
			else tmp.push_back({ item.num, item.cnt, item.t });
			v = tmp;
		}
	}
	else {
		if (v.size() < N) {
			v.push_back({ n, 1, t });
			visited[n] = true;
		}
		else {
			sort(v.begin(), v.end(), compare);
			visited[v[v.size() - 1].num] = false;
			v.pop_back();
			v.push_back({ n, 1, t });
			visited[n] = true;
		}
	}
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < K; ++i) {
		int n;
		cin >> n;
		update(i, n);
	}
	vector<int> answer;
	for (auto item : v) answer.push_back(item.num);
	sort(answer.begin(), answer.end(), less<int>());
	for (int x : answer) cout << x << ' ';
}