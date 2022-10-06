#pragma once
#include"Vector2.h"

class Camera
{
	static const float SHAKE_SPEED;
	//static const float SHAKE_SLOW_RATE;

	Vector2<float>_initPos;
	Vector2<float>_pos;

	//‰æ–Ê—h‚ê‚ÉŠÖ‚µ‚Ä
	bool _shakeFlag;
	float _shakeMove;
	float _oldShakeMove;
	float _shakeRate;
	float _beforePosX;

	int _a;

	float _toY;
	bool _scrollFlag;

public:
	Camera(Vector2<float> WindowSize);
	~Camera() {};

	void Initialize();
	void Update(const float &PlayerPosY);

	Vector2<float> GetCamPos()const;
	void CamShake();
};