#pragma once
#include <map>
#include <string>
#include"Stage.h"

using namespace std;

class Parameter {
public:
	const static int Error = -1;
	Parameter() = default;
	virtual ~Parameter() = default;

	void set(string key, int val);
	void set(string key, Stage* stageArrayPtr);
	int  get(string key) const;
	Stage* stageGet(string key)const;
private:
	map<string, int> _map;
	map<string, Stage*>_mapStage;
};

