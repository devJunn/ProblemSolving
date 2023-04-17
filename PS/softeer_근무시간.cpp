#include <iostream>
#include <string>

using namespace std;

int calcMinute(string t) {
	int ret = 0;
	int hour = stoi(t.substr(0, 2));
	int minute = stoi(t.substr(3, 2));
	ret = hour * 60 + minute;
	return ret;
}

int main() {
	int answer = 0;
	for (int day = 1; day <= 5; ++day) {
		string start, end;
		cin >> start >> end;
		answer += calcMinute(end) - calcMinute(start);
	}
	cout << answer << "\n";
}