#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<char> v;
string s1;
string s2;

bool check()
{
	if (v.size() < s2.size()) return false;
	for (int i = 0; i < s2.size(); i++)
	{
		if (s2[i] != v[v.size() - s2.size() + i]) return false;
	}
	return true;
}

int main()
{
	cin >> s1;
	v.reserve(s1.size());
	cin >> s2;
	int l = s2.size();
	for (int i = 0; i < s1.size(); i++)
	{
		v.push_back(s1[i]);
		if (check())
		{
			for (int j = 0; j < l; j++)
			{
				v.pop_back();
			}
		}
	}
	if (v.empty())
		cout << "FRULA";
	else
	{
		for (auto x : v)
		{
			cout << x;
		}
	}
}