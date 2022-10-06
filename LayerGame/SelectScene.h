#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include<vector>
#include"SelectObj.h"
#include"camera.h"
#include"Graphics.h"

class SelectScene : public AbstractScene {
public:
	static const char* CLEARED;
	static int TUTORIAL_GRAPH;

	SelectScene(IoChangedListener *impl, const Parameter &parameter,Fade* Fader,GoalEffect* GoalEffecter);
	virtual ~SelectScene();
	void init() override;
	void finalize() override;
	void update() override;
	void SelectUpdate();
	void draw() override;
private:
	static int _nowSelect;
	static bool _camScrollStartFlag;
	static int _clearStage;
	static int _bgGraph;
	static int _shadowGraph;

	bool leftFlag;
	bool rightFlag;

	bool clearedFlag;

	static StageDoorObj _entrance;
	std::vector<Stage*>_stageObj;
	Floor _floor;
	Camera camera;

	static const int PLAYER_SIZE = 340;
	static const Vector2<float> PLAYER_POS;

	LoopImage _playerGraph;
	AnimationImage _playerMagicGraph;

	bool sceneChangeFlag;

	bool _turn;
};