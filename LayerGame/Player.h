#pragma once
#include"StageInfoTransInterFace.h"
#include"Vector2.h"
#include"Graphics.h"

class Player
{
private:
	static int loadFlag;
	static LoopImage _graph;
	static LoopImage _holdGraph;
	static AnimationImage _magicGraph;

	StageInfoTransInterFace* _mTranser;

	Vector2<float>_pos;
	Vector2<float> _size;

	bool _moveFlag[4];

	//プレイヤー踏んでいるチップ
	int _whatOnChip;

	//伸縮
	Vector2<float> _normalSize;
	float _stretchSize;
	float _sizeChangeRate;

	//移動
	static const float MOVE_CHANGE_RATE;
	Vector2<float>_oldPos;
	Vector2<float>_toPos;
	float _moveChangeRate;

	bool _turn;

public:
	Player();
	~Player() {};

	void Init(StageInfoTransInterFace* Transer,float ChipSize);
	void InputInfoUpdate();
	void Stretch();
	void Update(bool CanMove);
	void Draw(bool Hold);

	int GetWhatOnPlayer() { return _whatOnChip; }
	Vector2<float> CenterPos() { return { _pos.x + _normalSize.x / 2,_pos.y + _normalSize.y / 2 }; }
};