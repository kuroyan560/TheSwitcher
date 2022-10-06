#pragma once
#include"Particle.h"

class WallKickParticleEmitter
{
	static const int PARTICLE_NUM = 30;
	static const int PARTICLE_SIZE = 10;
	static const int PARTICLE_EMIT_SPEED = 5;
	static const int PAL_CHANGE = 2;
	static const float G;

	FallBoxParticle* _particle[PARTICLE_NUM];

	bool aliveFlag;

public:
	WallKickParticleEmitter();
	~WallKickParticleEmitter();

	void Initialize();
	void Update();
	void Draw();
	void EmitKickSmoke(Vector2<float> initPos);

	bool GetAlive() { return aliveFlag; }
};
