#pragma once

#include <iostream>

class MyClass {
private:
	int a;
	int b;
	double d;
	const char* str = "Hi!This is pract 13.";

public:
	MyClass(int aVal, int bVal, double dVal) : a(aVal), b(bVal), d(dVal) {}

	int getA() const { return a; }
	int getB() const { return b; }
	double getD() const { return d; }
	const char* getStr() const { return str; }
};
