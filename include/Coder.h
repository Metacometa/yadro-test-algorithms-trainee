#pragma once
class Coder
{
	bool c = 0;
	bool b = 0;
	bool a = 0;

public:
	int getX() {
		return (c + b + a) % 2;
	}

	int getY() {
		return (c + a) % 2;
	}

	void push(const int& value) {
		a = b;
		b = c;
		c = value;
	}

	bool isEmpty() {
		return !(c or b or a);
	}

	void print() {
		std::cout << a << b << c << std::endl;
	}
};

