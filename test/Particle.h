#pragma once
#include"Vector2.h"

class Particle
{
public:
	const enum BLEND_MODE {
		ALPHA, ADD
	};

protected:
	static const int BLEND[2];

	int _maxSpeed;			//最大噴出速度
	Vector2<float> _pos;	//座標
	Vector2<float> _vel;	//移動量
	float _size;			//サイズ
	int _pal;				//不透明度
	int _palChange;

	BLEND_MODE _blendMode;

	bool _isAliveFlag;

public:
	virtual ~Particle() {};

	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Draw() = 0;

	virtual void Emit(Vector2<float> initPos) = 0;

	bool GetAlive() { return _isAliveFlag; }
};

//サイズ変更なし、四角を描画,落下なし
class BoxParticle :public Particle
{
	int _red;
	int _green;
	int _blue;

public:
	BoxParticle(int initSize, int maxEmitSpeed, int palChangeRate, BLEND_MODE blend, int r, int g, int b);
	~BoxParticle() {};

	virtual void Initialize()override;
	virtual void Draw()override;
	virtual void Emit(Vector2<float> initPos)override;
};

//サイズ変更なし、四角を描画,落下あり
class FallBoxParticle :public BoxParticle
{
	float _gravity;
	float _fallVel;

public:
	FallBoxParticle(int initSize, int maxEmitSpeed, int palChangeRate, BLEND_MODE blend, int r, int g, int b, float gravity);
	virtual void Update()override;
	virtual void Emit(Vector2<float>initPos)override;
};