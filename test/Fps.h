#pragma once
#include <list>

using namespace std;

class Fps {
public:
	Fps();
	void wait();
	void draw() const;

private:
	list<int> _list;
	float _fps;
	unsigned _counter;		//正の値だけでカウントする

	void updateAverage();
	void regist();
	unsigned getWaitTime() const;
};

