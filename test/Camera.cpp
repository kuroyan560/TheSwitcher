#include "Camera.h"
#include"easing.h"

const float Camera::SHAKE_SPEED = 8.0F;
//const float Camera::SHAKE_SLOW_RATE = -0.9;

static float lerp(float start, float end, float t)
{
	return (1 - t) * start + t * end;
}

static float value(float a)
{
	if (a < 0) {
		return -a;
	}
	else return a;
}

Camera::Camera(Vector2<float> WindowSize){
	_initPos = WindowSize / 2;
}

void Camera::Initialize(){
	_pos = _initPos;
	_shakeFlag = false;
	_shakeMove = 0.0F;
	_oldShakeMove = 0.0F;
	_beforePosX = 0.0F;
	_scrollFlag = false;
	_a = 1;
}

void Camera::Update(const float &PlayerPosY){

	//‰æ–Ê—h‚ê
	if (_shakeFlag) {
		_pos.x += (_shakeMove - _oldShakeMove);
		_oldShakeMove = _shakeMove;
		_shakeMove = (1 - Ease(Out, Elastic, _shakeRate)) * SHAKE_SPEED * _a;
		_a *= -1;

		if (_shakeMove == 0.0F){
			_pos.x = _beforePosX;
			_shakeFlag = false;
		}

		if (_shakeRate < 1.0F){
			_shakeRate += 0.1F;
			if (1.0F < _shakeRate) {
				_shakeRate = 1.0F;
			}
		}
	}

	if (_scrollFlag)
	{
		_pos.y = lerp(_pos.y, _toY, 0.1F);
		if (value(_pos.y - _toY) < 0.1F){
			_pos.y = _toY;
			_scrollFlag = false;
		}
	}

	if (PlayerPosY < _pos.y) {
		_toY = PlayerPosY;
		_scrollFlag = true;
	}
}

Vector2<float> Camera::GetCamPos()const{
	return (_pos - _initPos);
}

void Camera::CamShake(){
	if (!_shakeFlag){
		_beforePosX = _pos.x;
	}
	_oldShakeMove = 0.0F;
	_shakeRate = 0.0F;
	_shakeMove = SHAKE_SPEED;
	_shakeFlag = true;
}
