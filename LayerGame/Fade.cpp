#include "Fade.h"

const int Fade::ALPHA_SPEED = 10;

Fade::Fade() {

	//�V�[���`�F���W

	_sceneSize = { 1500,2500 };
	_sceneVelocity = { 0,120 };

	_downScenePos = { 0,-_sceneSize.y };
	_upScenePos = { 0,750 };

	_upSceneChangeFlag = false;
	_downSceneChangeFlag = false;
	_upDownScreenAllBlackFlag = false;

	_sceneGraph = LoadGraph("_resource/graphics/fadeGradation.png");


	//�Ó]
	_boxPos = { 0,0 };
	_boxSize = { 1280,728 };

	_alpha = 0;

	_startTurnDarkFlag = false;
	_gettingDarkFlag = false;

	_timer = 0;
	_stopTimerFlag = false;
	_turnAllBlackScreenFlag = false;

}

void Fade::Initialize() {

	_downSceneChangeFlag = false;
	_upSceneChangeFlag = false;

	_downScenePos = { 0,-_sceneSize.y};
	_upScenePos = { 0,_sceneSize.y };

	_upDownScreenAllBlackFlag = false;
	_turnAllBlackScreenFlag = false;
}

void Fade::Finalize() {
}

void Fade::Update() {


	UpdateChangeFloor();

	UpdateSceneChange();



	//��ʂ��^���ÂɂȂ�u��
	//���̃t���O�Ȃ���S�ɃV�[���؂�ւ����\
	if (_downScenePos.y >= -230) {

		_upDownScreenAllBlackFlag = true;

	}
	else if (_upScenePos.y <= -1400) {

		_upDownScreenAllBlackFlag = true;

	}
	//�Ó]���A���t���[�����~�܂�u��
	else if (_stopTimerFlag){

		_turnAllBlackScreenFlag = true;

	}

}

void Fade::UpdateChangeFloor() {

	//���w�Ɍ�����
	if (_downSceneChangeFlag) {

		if (_downScenePos.y <= 1000) {

			_downScenePos.y += _sceneVelocity.y;

		}
		else {

			_downScenePos = { 0,-_sceneSize.y - _sceneVelocity.y };
			_downSceneChangeFlag = false;
			_upDownScreenAllBlackFlag = false;

		}
	}


	//��w�Ɍ�����
	if (_upSceneChangeFlag) {

		if (_upScenePos.y >= -3000) {

			_upScenePos.y -= _sceneVelocity.y;

		}
		else {

			_upScenePos = { 0,_sceneSize.y + _sceneVelocity.y };
			_upSceneChangeFlag = false;
			_upDownScreenAllBlackFlag = false;

		}
	}

}

void Fade::UpdateSceneChange() {


	//�Ó]
	if (_startTurnDarkFlag) {


		if (0 >= _alpha) {

			_gettingDarkFlag = true;

		}
		else if (_alpha >= 255) {

			_stopTimerFlag = true;

		}


		if (!_stopTimerFlag) {

			if (_gettingDarkFlag) {

				_alpha += ALPHA_SPEED;

			}
			else {

				_alpha -= ALPHA_SPEED;

			}

		}


		if (_alpha <= 0) {

			_startTurnDarkFlag = false;

		}

		//���S�ɉ�ʂ�^���Âɂ��A�V�[���؂�ւ��̂��߂ɏ������Ԃ�҂����Ă���
		if (_stopTimerFlag) {

			_timer++;

			if (_timer > 10) {

				_stopTimerFlag = false;
				_gettingDarkFlag = false;
				_turnAllBlackScreenFlag = false;
				_alpha = 254;
				_timer = 0;
			}

		}

	}

}

void Fade::Draw() const {

	DrawSceneChange();

	DrawChangeFloor();

}

void Fade::DrawChangeFloor() const {

	if (_upSceneChangeFlag) {

		DrawExtendGraph(_upScenePos.x, _upScenePos.y, _upScenePos.x + _sceneSize.x, _upScenePos.y + _sceneSize.y, _sceneGraph, TRUE);

	}

	if (_downSceneChangeFlag) {

		DrawExtendGraph(_downScenePos.x, _downScenePos.y, _downScenePos.x + _sceneSize.x, _downScenePos.y + _sceneSize.y, _sceneGraph, TRUE);

	}

}
void Fade::DrawSceneChange() const {

	if (_startTurnDarkFlag) {

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawBox(_boxPos.x, _boxPos.y, _boxPos.x + _boxSize.x, _boxPos.y + _boxSize.y, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

}

void Fade::GoingUpFloor() {

	_upSceneChangeFlag = true;

}
void Fade::GoingDownFloor() {

	_downSceneChangeFlag = true;

}
void Fade::TurnBlack() {

	_startTurnDarkFlag = true;

}

bool Fade::ChangeFloorTrigger() {

	return _upDownScreenAllBlackFlag;

}

bool Fade::TurnBlackTrigger() {

	return _turnAllBlackScreenFlag;

}

bool Fade::NowFadeFlag()
{
	if (_downSceneChangeFlag || _upSceneChangeFlag ||  _gettingDarkFlag) {
		return true;
	}
	else {
		return false;
	}
}
