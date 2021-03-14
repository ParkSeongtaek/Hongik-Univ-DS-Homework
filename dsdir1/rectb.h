// 금속조형디자인과 3학년
// B743014 양혜진

#ifndef RECTANGLE_H
#define RECTANGLE_H
using namespace std;

class Rectangle {
public:
	Rectangle(int, int, int, int); //constructor
	bool operator<(Rectangle&);
	bool operator==(Rectangle&);
	int GetHeight();
	int GetWidth();
friend ostream& operator<<(ostream&, Rectangle&);
private:
	int xLow, yLow, height, width;
};

#endif
