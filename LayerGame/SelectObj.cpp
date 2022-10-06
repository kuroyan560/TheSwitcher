#include "SelectObj.h"
#include"WindowSize.h"
#include"DxLib.h"
#include"SoundEmitter.h"

void StageDoorObj::AddStageDoor(const char* FilePass){
	_graphLight.push_back(AnimationImage("_resource/graphics/entrance_light.png", true, 8, 4, { 8,1 }, { 86,86 }, 50, true, true));
	_graphEntrance.push_back(LoadGraph(FilePass));
	_posX.push_back(POS_X + GetWinSize().x * (_graphEntrance.size() - 1));
	clearFlag.push_back(false);
}

void StageDoorObj::Update(){
	for (int i = 0; i < _graphLight.size(); i++) {
		_graphLight[i].Update();
	}
}

void StageDoorObj::Draw(float CamPosX){
	for (int i = 0; i < _graphEntrance.size(); i++) {
		float x = _posX[i] - CamPosX;

		if ((i != 0 && !clearFlag[i] && clearFlag[i - 1]) || i==0) {
			DrawGraph(x, POS_Y, _graphEntrance[i], true);
		}
		else if (!clearFlag[i]) {
			SetDrawBright(100, 100, 100);
			DrawGraph(x, POS_Y, _graphEntrance[i], true);
			SetDrawBright(255, 255, 255);
		}
		if(clearFlag[i]) {
			DrawGraph(x, POS_Y, _graphEntrance[i], true);
			_graphLight[i].Draw({ x + ENTRANCE_WIDTH / 2 + 5,POS_Y+65 }, { 86,86 });
		}
	}
}

void StageDoorObj::LightAnimation(int StageNum){
	if (_graphLight[StageNum].NowAnimation() == false) {
		PlaySE(SHINE);
	}
	_graphLight[StageNum].AnimationStart();
}

bool StageDoorObj::AnimationComplete(int StageNum)
{
	return _graphLight[StageNum].DrawComplete();
}

int Floor::graph = 0;

Floor::Floor(){
	if (graph == 0) {
		graph = LoadGraph("_resource/graphics/floor.png");
	}
}

void Floor::Init(const int StageMax){
	for (int i = 0; i < StageMax; i++) {
		posX.push_back(i * GetWinSize().x);
	}
}

void Floor::Draw(float CamPosX){
	for(int i = 0; i < posX.size(); i++) {
		DrawGraph(posX[i] - CamPosX, GetWinSize().y - HEIGHT, graph, true);
	}
}
