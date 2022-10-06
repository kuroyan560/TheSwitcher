#pragma once
#include"Particle.h"
class ExplosionEmitter : public ParticleInfoTranser{

	static const int PARTICLE_MAX = 40;
	static const int PARTICLE_SIZE = 128;
	static const int MAX_EMIT_SPEED = 10;
	static const float PARTICLE_CHANGE_SPEED;

	ExplosionParticle *_particles[PARTICLE_MAX];
	bool _aliveFlag;

public:
	ExplosionEmitter();
	~ExplosionEmitter();

	void Init();
	void Update();
	void Draw();
	void Emit(Vector2<float> Pos);

	bool GetAliveFlag() { return _aliveFlag; }
	virtual void EmitterDead()override { _aliveFlag = false; }
};