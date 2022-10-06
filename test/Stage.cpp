#include "Stage.h"
#include"WallAndFloor.h"
#include"WindowSize.h"

//�v���C���[������X�e�[�W
int Stage::PLAYER_STAGE = 0;

//�G�ƃA�C�e���̍��W�ݒ�i���x���f�U�C���ł�����Ƃ��j============================

//�X�e�[�W�P
InitPos Stage1::enemyInitPos[ENEMY_NUM] = {
	{4,10},{2,20}
};
InitPos Stage1::itemInitPos[ITEM_NUM] = {
	{6,15},{3,25}
};

//�X�e�[�W�Q
InitPos Stage2::enemyInitPos[ENEMY_NUM] = {
	{4,10},{2,20}
};
InitPos Stage2::itemInitPos[ITEM_NUM] = {
	{6,15},{3,25}
};

//�X�e�[�W�R
InitPos Stage3::enemyInitPos[ENEMY_NUM] = {
	{4,10},{2,20}
};
InitPos Stage3::itemInitPos[ITEM_NUM] = {
	{6,15},{3,25}
};

//================================================================================


Stage::Stage(int BPM, int WallHeight){
	_bpm = BPM;
	_fpsPerBit = 3600 / _bpm;		//3600fps=�P��
	_wallHeight = WallHeight;
	_heightPerBit = _wallHeight / BAR_NUM / 4;
	_wallBetweenWalls = GetWinSize().x - WallAndFloor::WALL_WIDTH * 2;
	_widthPerBit = _wallBetweenWalls / 8;
}

Stage1::Stage1(int BPM, int WallHeight) :Stage(BPM, WallHeight) {
}

void Stage1::Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj){
	
	//�G�̈ʒu������
	for (int i = 0; i < ENEMY_NUM; i++){
		if (EnemyObjArray + i != NULL){
			(EnemyObjArray + i)->Initialize(enemyInitPos[i].x, enemyInitPos[i].y, _widthPerBit, _heightPerBit, UPDOWN);
		}
	}

	//�A�C�e���̈ʒu������
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
	//�G�̈ʒu������
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (EnemyObjArray + i != NULL) {
			(EnemyObjArray + i)->Initialize(enemyInitPos[i].x, enemyInitPos[i].y, _widthPerBit, _heightPerBit, UPDOWN);
		}
	}

	//�A�C�e���̈ʒu������
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
	//�G�̈ʒu������
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (EnemyObjArray + i != NULL) {
			(EnemyObjArray + i)->Initialize(enemyInitPos[i].x, enemyInitPos[i].y, _widthPerBit, _heightPerBit, UPDOWN);
		}
	}

	//�A�C�e���̈ʒu������
	for (int i = 0; i < ITEM_NUM; i++) {
		if (ItemObjArray + i != NULL) {
			(ItemObjArray + i)->Initialize(itemInitPos[i].x, itemInitPos[i].y, _widthPerBit, _heightPerBit);
		}
	}

	GoalObj.Initialize(_wallHeight);
}
