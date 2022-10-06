#include "Emitter.h"
#include"DxLib.h"

const float WallKickParticleEmitter::G = 0.06F;

WallKickParticleEmitter::WallKickParticleEmitter()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		int a = GetRand(240-50) + 100;
		_particle[i] = new FallBoxParticle(PARTICLE_SIZE, PARTICLE_EMIT_SPEED, PAL_CHANGE, Particle::BLEND_MODE::ALPHA, a, a, a);
	}
}

WallKickParticleEmitter::~WallKickParticleEmitter()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		delete _particle[i];
	}
}

void WallKickParticleEmitter::Initialize()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		_particle[i]->Initialize();
	}
}

void WallKickParticleEmitter::Update()
{
	aliveFlag = false;

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		_particle[i]->Update();
		if (_particle[i]->GetAlive() == true)
		{
			aliveFlag = true;
		}
	}
}

void WallKickParticleEmitter::Draw()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		_particle[i]->Draw();
	}
}

void WallKickParticleEmitter::EmitKickSmoke(Vector2<float> initPos)
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		_particle[i]->Emit(initPos);
	}
}
