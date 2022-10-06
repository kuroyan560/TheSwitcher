#include "Parameter.h"

//�p�����[�^�Z�b�g
void Parameter::set(string key, int val) {
	_map[key] = val;
}

void Parameter::set(string key, Stage* stageArrayPtr) {
	_mapStage[key] = stageArrayPtr;
}

//�p�����[�^�擾
int Parameter::get(string key) const {
	auto it = _map.find(key);	//�L�[�擾
	if (_map.end() == it) {
		return Error;
	}
	else {
		return it->second;
	}
}

Stage* Parameter::stageGet(string key) const
{
	auto it = _mapStage.find(key);	//�L�[�擾
	if (_mapStage.end() == it) {
		return nullptr;
	}
	else {
		return it->second;
	}
}
