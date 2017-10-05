#ifndef __LINE_H__	//guard against cyclic dependancy
#define __LINE_H__

class Line{
public:
	Line();	//constructor
	void drawLine();

	float publicVar;
private:
	float privateVar;
};

#endif