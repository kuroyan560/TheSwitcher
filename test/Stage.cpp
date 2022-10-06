#include "Stage.h"
#include"WallAndFloor.h"
#include"WindowSize.h"

//プレイヤーがいるステージ
int Stage::PLAYER_STAGE = 0;

//敵とアイテムの座標設定（レベルデザインでいじるとこ）============================

//ステージ１
InitPos Stage1::enemyInitPos[ENEMY_NUM] = {
	{4,10},{2,20}
};
InitPos Stage1::itemInitPos[ITEM_NUM] = {
	{6,15},{3,25}
};

//ステージ２
InitPos Stage2::enemyInitPos[ENEMY_NUM] = {
	{4,10},{2,20}
};
InitPos Stage2::itemInitPos[ITEM_NUM] = {
	{6,15},{3,25}
};

//ステージ３
InitPos Stage3::enemyInitPos[ENEMY_NUM] = {
	{4,10},{2,20}
};
InitPos Stage3::itemInitPos[ITEM_NUM] = {
	{6,15},{3,25}
};

//================================================================================


Stage::Stage(int BPM, int WallHeight){
	_bpm = BPM;
	_fpsPerBit = 3600 / _bpm;		//3600fps=１分
	_wallHeight = WallHeight;
	_heightPerBit = _wallHeight / BAR_NUM / 4;
	_wallBetweenWalls = GetWinSize().x - WallAndFloor::WALL_WIDTH * 2;
	_widthPerBit = _wallBetweenWalls / 8;
}

Stage1::Stage1(int BPM, int WallHeight) :Stage(BPM, WallHeight) {
}

void Stage1::Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj){
	
	//敵の位置初期化
	for (int i = 0; i < ENEMY_NUM; i++){
		if (EnemyObjArray + i != NULL){
			(EnemyObjArray + i)->Initialize(enemyInitPos[i].x, enemyInitPos[i].y, _widthPerBit, _heightPerBit, UPDOWN);
		}
	}

	//アイテムの位置初期化
	for (int i = 0; i < ITEM_NUM; i++){
		if (ItemObjArray + i != NULL){
			(ItemObjArray + i)->Initialize(itemInitPos[i].x, itemInitPos[i].y, _widthPerBit, _heightPerBit);
		}
	}

	GoalObj.Initialize(_wallHeight);
}

Stage2::Stage2(int BPM, int WallHeight) :Stage(BPM, WallHeight) {
}

void Stage2::Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj)
{
	//敵の位置初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (EnemyObjArray + i != NULL) {
			(EnemyObjArray + i)->Initialize(enemyInitPos[i].x, enemyInitPos[i].y, _widthPerBit, _heightPerBit, UPDOWN);
		}
	}

	//アイテムの位置初期化
	for (int i = 0; i < ITEM_NUM; i++) {
		if (ItemObjArray + i != NULL) {
			(ItemObjArray + i)->Initialize(itemInitPos[i].x, itemInitPos[i].y, _widthPerBit, _heightPerBit);
		}
	}

	GoalObj.Initialize(_wallHeight);
}

Stage3::Stage3(int BPM, int WallHeight) :Stage(BPM, WallHeight) {
}

void Stage3::Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj)
{
	//敵の位置初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (EnemyObjArray + i != NULL) {
			(EnemyObjArray + i)->Initialize(enemyInitPos[i].x, enemyInitPos[i].y, _widthPerBit, _heightPerBit, UPDOWN);
		}
	}

	//アイテムの位置初期化
	for (int i = 0; i < ITEM_NUM; i++) {
		if (ItemObjArray + i != NULL) {
			(ItemObjArray + i)->Initialize(itemInitPos[i].x, itemInitPos[i].y, _widthPerBit, _heightPerBit);
		}
	}

	GoalObj.Initialize(_wallHeight);
}
