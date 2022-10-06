#include "Player.h"
#include"UsersInput.h"
#include"DxLib.h"
#include"WindowSize.h"
#include"easing.h"
#include"SoundEmitter.h"

int Player::loadFlag = 0;
LoopImage Player::_graph = LoopImage();
LoopImage Player::_holdGraph = LoopImage();
AnimationImage Player::_magicGraph = AnimationImage();

const float Player::MOVE_CHANGE_RATE = 0.115F;

Player::Player() {
	if (loadFlag == 0) {
		_graph.Init("_resource/graphics/player_wait.png", true, 5, 15, { 5,1 }, { 65,65 });
		_holdGraph.Init("_resource/graphics/player_hold.png", true, 3, 8, { 3,1 }, { 64,64 });
		_magicGraph.Init("_resource/graphics/player_magic.png", true, 6, 6, { 6,1 }, { 64,64 }, 35, true);
		loadFlag = 1;
	}
}

void Player::Init(StageInfoTransInterFace* Transer, float ChipSize){
	_mTranser = Transer;
	_pos = { ChipSize * _mTranser->GetPlayerSpawnPos().x,ChipSize * _mTranser->GetPlayerSpawnPos().y };
	_toPos = _pos;
	_oldPos = _pos;
	_size = { ChipSize,ChipSize };

	_normalSize = _size;

	//伸縮する分のサイズ
	_stretchSize = ChipSize / 12;
	_sizeChangeRate = 1.0F;

	//移動変化率リセット
	_moveChangeRate = 1.0F;

	for (int i = 0; i < 4; i++) {
		_moveFlag[i] = false;
	}

	_turn = false;
}

void Player::InputInfoUpdate(){

	for (int i = 0; i < 4; i++) {
		_moveFlag[i] = false;
	}

	if (_moveChangeRate == 1.0F) {
		if (Press(KEY_INPUT_UP) && _mTranser->GetMapData({ _pos.x,_pos.y - _normalSize.y }) != WALL) {
			_moveFlag[MOVE_UP] = true;
			_moveChangeRate = 0.0F;
			_oldPos = _pos;
		}
		else if (Press(KEY_INPUT_DOWN) && _mTranser->GetMapData({ _pos.x,_pos.y + _normalSize.y }) != WALL) {
			_moveFlag[MOVE_DOWN] = true;
			_moveChangeRate = 0.0F;
			_oldPos = _pos;
		}
		else if (Press(KEY_INPUT_LEFT)) {
			if (_mTranser->GetMapData({ _pos.x - _normalSize.x,_pos.y }) != WALL) {
				_moveFlag[MOVE_LEFT] = true;
				_moveChangeRate = 0.0F;
				_oldPos = _pos;
			}
			_turn = false;
		}
		else if (Press(KEY_INPUT_RIGHT)) {
			if (_mTranser->GetMapData({ _pos.x + _normalSize.x,_pos.y }) != WALL) {
				_moveFlag[MOVE_RIGHT] = true;
				_moveChangeRate = 0.0F;
				_oldPos = _pos;
			}
			_turn = true;
		}
	}
	if (_sizeChangeRate == 1.0F || _moveChangeRate == 0.0F) {
		if (Press(KEY_INPUT_UP) || Press(KEY_INPUT_DOWN) || Press(KEY_INPUT_RIGHT) || Press(KEY_INPUT_LEFT)) {
			_sizeChangeRate = 0.0F;
			PlaySE(MOVE);
		}
	}
}

void Player::Stretch()
{
	_size.x = _normalSize.x	- _stretchSize * (1 - Ease(InOut, Cubic, _sizeChangeRate));
	_size.y = _normalSize.y + _stretchSize * (1 - Ease(InOut, Cubic, _sizeChangeRate));

	if (_sizeChangeRate < 1.0F)
	{
		_sizeChangeRate += 0.05F;

		if (1.0F < _sizeChangeRate)
		{
			_sizeChangeRate = 1.0F;
		}
	}
}

void Player::Update(bool CanMove) {

	//魔法使う画像の更新
	_magicGraph.Update();

	//スイッチを踏む
	if (CanMove && JustOut(KEY_INPUT_SPACE) == true && _moveChangeRate == 1.0F) {
		int i = 0;
		i = _mTranser->PressSwitch(_whatOnChip);

		if (i == 1) {
			_magicGraph.AnimationStart();
		}
	}

	_whatOnChip = _mTranser->GetMapData(CenterPos());

	if (_whatOnChip != GOAL) {
		if (_magicGraph.NowAnimation() == false && CanMove) {
			InputInfoUpdate();
		}
	}
	else {
		if (_moveChangeRate == 1.0F) {
			_mTranser->ReachGoal();
		}
	}

	Stretch();

	if (_moveChangeRate < 1.0F)
	{
		_moveChangeRate += MOVE_CHANGE_RATE;

		if (1.0F < _moveChangeRate)
		{
			_moveChangeRate = 1.0F;
		}
	}

	//移動演出用
	_pos.x = (_toPos.x - _oldPos.x) * Ease(InOut, Cubic, _moveChangeRate) + _oldPos.x;
	_pos.y = (_toPos.y - _oldPos.y) * Ease(InOut, Cubic, _moveChangeRate) + _oldPos.y;

	//移動
	if (_moveFlag[MOVE_UP] == true) {
		_toPos.y = _pos.y - _normalSize.y;
	}
	else if (_moveFlag[MOVE_DOWN] == true) {
		_toPos.y = _pos.y + _normalSize.y;
	}
	else if (_moveFlag[MOVE_LEFT] == true) {
		_toPos.x = _pos.x - _normalSize.x;
	}
	else if (_moveFlag[MOVE_RIGHT] == true) {
		_toPos.x = _pos.x + _normalSize.x;;
	}
}

void Player::Draw(bool Hold) {
	if (_magicGraph.NowAnimation() == false) {
		if (Hold) {
			_holdGraph.Draw(CenterPos(), _size);
		}
		else {
			_graph.Draw(CenterPos(), _size, _turn);
		}
	}
	_magicGraph.Draw(CenterPos(), _size,_turn);
}