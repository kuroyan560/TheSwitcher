#include "Particle.h"
#include<math.h>
#include"DxLib.h"

const int Particle::BLEND[2] = { DX_BLENDMODE_ALPHA,DX_BLENDMODE_ADD };

void Particle::Update()
{
	if (_isAliveFlag) {

		_pal -= _palChange;
		if (_pal < 0) {
			_isAliveFlag = false;
		}

		_pos += _vel;
	}
}


BoxParticle::BoxParticle(int initSize,int maxEmitSpeed,int palChangeRate,BLEND_MODE blend, int r, int g, int b)
{
	_size = initSize;
	_maxSpeed = maxEmitSpeed;
	_palChange = palChangeRate;
	_blendMode = blend;
	_red = r;
	_green = g;
	_blue = b;
}

void BoxParticle::Initialize()
{
	_isAliveFlag = false;
}

void BoxParticle::Draw()
{
	if (_isAliveFlag)
	{
		SetDrawBlendMode(BLEND[_blendMode], _pal);
		DrawBox(_pos.x, _pos.y, _pos.x + _size, _pos.y + _size, GetColor(_red, _green, _blue), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void BoxParticle::Emit(Vector2<float> initPos)
{
	_pos = { initPos.x - _size / 2,initPos.y - _size / 2 };
	_pal = 255;
	float angle = GetRand(360) * DX_PI / 180;
	Vector2<float>_vec = { cos(angle),sin(angle) };
	_vel = _vec * (GetRand(_maxSpeed - 1) + 1);
	_isAliveFlag = true;
}

FallBoxParticle::FallBoxParticle(int initSize, int maxEmitSpeed, int palChangeRate, BLEND_MODE blend, int r, int g, int b, float gravity)
	:BoxParticle{ initSize, maxEmitSpeed, palChangeRate, blend, r, g, b }
{
	_gravity = gravity;
}

void FallBoxParticle::Update()
{
	if (_isAliveFlag) {

		_pal -= _palChange;
		if (_pal < 0) {
			_isAliveFlag = false;
		}

		_fallVel += _gravity;
		_vel.y += _fallVel;

		_pos += _vel;
	}
}

void FallBoxParticle::Emit(Vector2<float> initPos)
{
	_pos = { initPos.x - _size / 2,initPos.y - _size / 2 };
	_pal = 255;
	float angle = GetRand(360) * DX_PI / 180;
	Vector2<float>_vec = { cos(angle),sin(angle) };
	_vel = _vec * (GetRand(_maxSpeed - 1) + 1);
	_fallVel = 0.0F;
	_isAliveFlag = true;
}
