#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int R, C;
char board[20][20];
vector<string> words;

int main()
{
	cin >> R >> C;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> board[i][j];
		}
	}

	for (int i = 0; i < R; i++)
	{
		int j = 0;
		string word = "";
		while (j < C)
		{
			if (board[i][j] == '#')
			{
				if (word != "")
				{
					if (word.size() > 1) words.push_back(word);
					word = "";
				}
				++j;
				continue;
			}
			word += board[i][j];
			++j;
		}
		if (word.size() > 1) words.push_back(word);
	}

	for (int j = 0; j < C; j++)
	{
		int i = 0;
		string word = "";
		while (i < R)
		{
			if (board[i][j] == '#')
			{
				if (word != "")
				{
					if (word.size() > 1) words.push_back(word);
					word = "";
				}
				++i;
				continue;
			}
			word += board[i][j];
			++i;
		}
		if (word.size() > 1) words.push_back(word);
	}

	sort(words.begin(), words.end(), less<string>());
	cout << words[0] << '\n';
}