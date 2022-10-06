#pragma once
#include"Graphics.h"
#include<vector>

class StageDoorObj{
private:
	static const int POS_X = 620;
	static const int POS_Y = 150;
	static const int ENTRANCE_WIDTH = 500;
	std::vector<AnimationImage> _graphLight;
	std::vector<int> _graphEntrance;
	std::vector<float> _posX;
	std::vector<bool> clearFlag;

public:
	StageDoorObj() {};
	~StageDoorObj() {};

	void AddStageDoor(const char* FilePass);
	void Update();
	void Draw(float CamPosX);
	void RaiseClearFlag(int StageNum) { clearFlag[StageNum] = true; }
	void LightAnimation(int StageNum);
	bool AnimationComplete(int StageNum);
};

class Floor {
private:
	static const int HEIGHT = 174;
	static int graph;

	std::vector<float> posX;

public:
	Floor();
	~Floor() {};

	void Init(const int StageMax);
	void Draw(float CamPosX);
};