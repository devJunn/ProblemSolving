#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int K;
char ops[9];
bool used[10];
vector<long long> answers;

bool op(int a, int b, char c)
{
	if (c == '<') return a < b;
	else return a > b;
}

void dfs(int curr, string num, int cnt = 0)
{
	if (cnt == K)
	{
		answers.push_back(stoll(num));
		return;
	}

	for (int nxt = 0; nxt < 10; nxt++)
	{
		if (used[nxt]) continue;

		if (op(curr, nxt, ops[cnt]))
		{
			used[nxt] = true;
			num += to_string(nxt);
			dfs(nxt, num, cnt + 1);
			num.pop_back();
			used[nxt] = false;
		}
	}
}

string lltos(long long num)
{
	string ret = to_string(num);
	if (ret.size() != K + 1) ret = "0" + ret;
	return ret;
}

int main()
{
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		cin >> ops[i];
	}
	for (int i = 0; i < 10; i++)
	{
		used[i] = true;
		dfs(i, to_string(i));
		used[i] = false;
	}
	sort(answers.begin(), answers.end(), less<long long>());
	cout << lltos(answers[answers.size() - 1]) << '\n';
	cout << lltos(answers[0]) << '\n';
}