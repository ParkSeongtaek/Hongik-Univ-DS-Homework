// 금속조형디자인과 3학년
// B743014 양혜진

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
	Rectangle(int x, int y, int h, int w); //constructor
	void Print();
	bool SmallerThan(Rectangle&); //면적이 작은가
	bool EqualTo(Rectangle&); // 면적이 같은가
	int GetHeight();
	int GetWidth();
private:
	int xLow, yLow, height, width;
};

#endif
