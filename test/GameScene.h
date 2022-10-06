#pragma once
#include "AbstractScene.h"
#include "Score.h"
#include "Stage.h"
#include "Enemy.h"
#include "Item.h"
#include "Goal.h"
#include "Camera.h"
#include "Player.h"
#include "WallAndFloor.h"
#include "Ui.h"
#include "DxLib.h"

class GameScene : public AbstractScene
{
public:
	const static char *StageTag;

	GameScene(IoChangedListener *impl, const Parameter &parameter);
	~GameScene();
	void init() override;
	void finalize() override;
	void update() override;
	void draw() const override;

private:
	Stage **stageObj;
	Score score;
	Enemy enemy[5];
	Item item[5];
	Goal goal;
	Camera camera;
	WallAndFloor waf;
	Ui ui;
	Player _player;
	int _counter;
	int _selectTag;

	bool HitCheck(Vector2<float> playerPos, Vector2<float> playerSize, Vector2<float> objPos, Vector2<float> objSize);
	void WallAndFloorCheck();

	//ÉäÉ\Å[ÉXì«Ç›çûÇ›
	int lowTap = LoadSoundMem("low_tap.mp3");
	void playBPM();
};