#pragma once
#include"Enemy.h"
#include"Item.h"
#include"Goal.h"

//�G��A�C�e���̈ʒu�ݒ�p�\����==================================================

struct InitPos{

	int x;		//�i�P�`�U�̒l������j
	int y;
};

class Stage{

protected:
	static const int BAR_NUM = 10;	//�P�X�e�[�W�ɂ������߂�

	int _bpm;				//�X�e�[�W���Ƃ̋Ȃ�bpm
	int _fpsPerBit;			//��fps�łP�����ނ�
	int _wallHeight;		//�ǂ̍��� =�i�ʐ^�ł����Ƃ���́jHeight
	float _heightPerBit;	//�P�����̍��� =�i�ʐ^�ł����Ƃ���́jy
	int _wallBetweenWalls;	//�ǂƕǂ̊Ԃ̍L�� =�i�ʐ^�ł����Ƃ���́jWidth
	float _widthPerBit;

public:
	static int PLAYER_STAGE;
	Stage(int BPM, int WallHeight);	//bpm�A��ԏ�܂ł̕ǂ̍����A�ǂƕǂ̊Ԃ̋���
	~Stage() {};

	virtual void Init(Enemy* EnemyObjArray, Item* ItemObjArray, Goal& GoalObj) = 0;

	int GetFPB() { return _fpsPerBit; }
	int GetWallHeight() { return _wallHeight; }
	int GetWallBetweenWidth() { return _wallBetweenWalls; }
	float GetHPB() { return _heightPerBit; }
};

//�X�e�[�W1
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

//�X�e�[�W2
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

//�X�e�[�W3
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