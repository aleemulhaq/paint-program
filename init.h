#ifndef __INIT_H__	//guard against cyclic dependancy
#define __INIT_H__

class Init{
public:
	Init();	//constructor
	void init(void);

	float publicVar;
private:
	float privateVar;
};

#endif