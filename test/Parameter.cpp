#include "..\LayerGame\Parameter.h"
#include "Parameter.h"

//パラメータセット
void Parameter::set(string key, int val) {
	_map[key] = val;
}

void Parameter::set(string key, Stage* stageArrayPtr)
{
}

//パラメータ取得
int Parameter::get(string key) const {
	auto it = _map.find(key);	//キー取得
	if (_map.end() == it) {
		return Error;
	}
	else {
		return it->second;
	}
}
