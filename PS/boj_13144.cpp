#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
bool check[100001];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		v.push_back(x);
	}
	long long ret = 0;
	int left = 0, right = 0;
	while (right < N) {
		if (check[v[right]]) {
			ret += (right - left);
			check[v[left]] = false;
			++left;
		}
		else {
			check[v[right]] = true;
			++right;
		}
	}
	ret += (long long) (right - left) * (long long) (right - left + 1) / 2;
	cout << ret << '\n';
}