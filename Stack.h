#ifndef STACK_H_
#define STACK_H_
using namespace std;

class MyStack {
private:
	int* items;
	int topIndex = -1;

public:
	MyStack(int c);
	void push(int e);
	int pop();
	int size();
	bool isEmpty();
};

#endif 