#pragma once
#include<vector>
#include"MapData.h"
#include"Vector2.h"
#include"StageInfoTransInterFace.h"
#include"Graphics.h"
#include"Emitter.h"
#include"Fade.h"
#include"GameMgrTranser.h"

class Stage : public StageInfoTransInterFace {

private:
	static int NUM_GRAPH[6];
	static int ARROW_GRAPH;
	static LoopImage MOVE_UP_GRAPH;
	static LoopImage MOVE_DOWN_GRAPH;
	static int MAGIC_CIRCLE_GRAPH;
	static int PLAYER_LAYER_BOX_GRAPH;

	std::vector<LayerMapData> _mapData;

	//���C���[�}�b�vUI�̕`����W
	float _layerY;

	//���~���̃}�b�v�k�ڂ�
	int _mapSizeChipNum;
	float _chipSize;

	//�v���C���[�̏������ʒu
	Vector2<float> _playerSpawnPos;
	int _playerSpawnLayer;

	//�v���C���[�����郌�C���[
	int _playerLayer;

	//�v���C���[������}�b�v���͂��Ԃ��l�p�̍�����W
	Vector2<float>_playerMapBoxPos;
	Vector2<float>_playerMapTo;

	//���ʂ̕\���ʒu
	Vector2<float> _markPos;

	//�N���A�[�t���O
	bool _clearFlag;

	//�~�j�}�b�v���@�w
	bool _magicCircleDrawFlag;
	float _magicCircleAngle;

	//�R�s�[���̔����G�~�b�^�[
	static const int EXPLOSION_EMITTER_NUM = 10;
	ExplosionEmitter _expEmitter[EXPLOSION_EMITTER_NUM];

	//�t�F�[�h�I�u�W�F�N�g�̃|�C���^
	Fade* _fadePtr;

	//�Q�[���V�[���Ƃ̑���
	GameMgrTranser* _mGameScene;

	//�ړ�����
	bool _floorUpFlag;
	bool _floorDownFlag;

	bool _resetFlag;

public:
	Stage();
	~Stage() {};

	//�ݒ�p�֐�
	void SetMapChipNum(int Num);
	void AddMapData(char *MapArray);
	void SetPlayerSpawnPos(Vector2<float> Pos,int Layer);

	//�������p�֐�
	void Init(Fade* FadeObj,GameMgrTranser* GameScene);
	void PlayerMapBoxPosInit();

	//���󂯓n���֐�
	float GetMapChipSize() { return _chipSize; }

	//���󂯓n���֐��i�p���j
	virtual Vector2<float> GetPlayerSpawnPos()const override{ return _playerSpawnPos; }
	virtual int GetMapData(Vector2<float> CenterPos)override;
	virtual int PressSwitch(int WhatSwitch)override;
	virtual void ReachGoal()override;

	void Update(const int WhatOnPlayer);
	void ExplosionEmit(const int WhatOnPlayer);
	void Draw(const int WhatOnPlayer);
	void MiniMapDraw(const int WhatOnPlayer);
	void PlayerMapBoxDraw();

	bool GetGoalFlag()const { return _clearFlag; }

	LayerMapData& GetNowMap();
};