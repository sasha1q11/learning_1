#include "checker.h"

std::wstring checkEven(int number) {
	if (number % 2 == 0) {
		return L"×èñëî " + std::to_wstring(number) + L" — ×¨ÒÍÎÅ ";
	}
	else {
		return L"×èñëî " + std::to_wstring(number) + L" — ÍÅ×¨ÒÍÎÅ ";
	}
}