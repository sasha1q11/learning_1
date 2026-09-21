#include <iostream>
#include <string>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	string input;
	cout << "Введите строку: ";
	getline(cin, input);
	string cleaned;
	for (char c : input) {
		if (!isspace(static_cast<unsigned char>(c))) {
			cleaned += tolower(static_cast<unsigned char>(c));
		}
	}
	int left = 0;
	int right = static_cast<int>(cleaned.length()) - 1;
	bool isPalindrome = true;

	while (left < right) {
		if (cleaned[left] != cleaned[right]) {
			isPalindrome = false;
			break;
		}
		left++;
		right--;
	}
	if (isPalindrome) {
		cout << "Строка является палиндромом." << endl;
	}
	else {
		cout << "Строка НЕ является палиндромом." << endl;
	}
	system ("pause");
	return 0;
}
