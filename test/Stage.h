#pragma once
#include"Enemy.h"
#include"Item.h"
#include"Goal.h"

//敵やアイテムの位置設定用構造体==================================================

struct InitPos{

	int x;		//（１～６の値が入る）
	int y;
};

class Stage{

protected:
	static const int BAR_NUM = 10;	//１ステージにつき何小節か

	int _bpm;				//ステージごとの曲のbpm
	int _fpsPerBit;			//何fpsで１拍刻むか
	int _wallHeight;		//壁の高さ =（写真でいうところの）Height
	float _heightPerBit;	//１拍分の高さ =（写真でいうところの）y
	int _wallBetweenWalls;	//壁と壁の間の広さ =（写真でいうところの）Width
	float _widthPerBit;

public:
	static int PLAYER_STAGE;
	Stage(int BPM, int WallHeight);	//bpm、一番上までの壁の高さ、壁と壁の間の距離
	~Stage() {};

	virtual void Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj) = 0;

	int GetFPB() { return _fpsPerBit; }
	int GetWallHeight() { return _wallHeight; }
	int GetWallBetweenWidth() { return _wallBetweenWalls; }
	float GetHPB() { return _heightPerBit; }
};

//ステージ1
class Stage1 :public Stage{

	static const int ENEMY_NUM = 2;
	static const int ITEM_NUM = 2;
	static InitPos enemyInitPos[ENEMY_NUM];
	static InitPos itemInitPos[ITEM_NUM];

public:
	Stage1(int BPM, int WallHeight);
	~Stage1() {};

	virtual void Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj)override;
};

//ステージ2
class Stage2 :public Stage {

	static const int ENEMY_NUM = 2;
	static const int ITEM_NUM = 2;
	static InitPos enemyInitPos[ENEMY_NUM];
	static InitPos itemInitPos[ITEM_NUM];

public:
	Stage2(int BPM, int WallHeight);
	~Stage2() {};

	virtual void Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj)override;
};

//ステージ3
class Stage3 :public Stage {

	static const int ENEMY_NUM = 2;
	static const int ITEM_NUM = 2;
	static InitPos enemyInitPos[ENEMY_NUM];
	static InitPos itemInitPos[ITEM_NUM];

public:
	Stage3(int BPM, int WallHeight);
	~Stage3() {};

	virtual void Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj)override;
};