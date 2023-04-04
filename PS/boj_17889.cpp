#include <iostream>

using namespace std;

bool check[10001];

int main() {
	int year = 2018;
	int month = 4;
	while (year <= 10000) {
		check[year] = true;
		year += 2;
		month += 2;
		if (month > 12) {
			year += 1;
			month -= 12;
		}
	}
	int x;
	cin >> x;
	check[x] ? cout << "yes\n" : cout << "no\n";
}