#pragma once
#define INFINITY   0xfffffffffffffffe

class Link
{
private:
	int From_Node;
	int To_Node;
	double Length; // cost of link
public:
	Link(void);
	~Link(void);
	void fill(char s[]);
	void write(char ff[20]);
	int get_From_Node();
	int get_To_Node();
	double get_Length();
};

