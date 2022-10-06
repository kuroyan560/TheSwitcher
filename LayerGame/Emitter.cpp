#include"Emitter.h"
#include"DxLib.h"

const float ExplosionEmitter::PARTICLE_CHANGE_SPEED = 0.01F;

ExplosionEmitter::ExplosionEmitter(){
	for (int i = 0; i < PARTICLE_MAX; i++) {
		_particles[i] = new ExplosionParticle(this,PARTICLE_SIZE, MAX_EMIT_SPEED, PARTICLE_CHANGE_SPEED, Particle::ADD);
	}
}

ExplosionEmitter::~ExplosionEmitter(){
	for (int i = 0; i < PARTICLE_MAX; i++) {
		delete _particles[i];
	}
}

void ExplosionEmitter::Init(){
	_aliveFlag = false;
	for (int i = 0; i < PARTICLE_MAX; i++) {
		_particles[i]->Initialize();
	}
}

void ExplosionEmitter::Update(){
	for (int i = 0; i < PARTICLE_MAX; i++) {
		_particles[i]->Update();
	}
}

void ExplosionEmitter::Draw(){
	for (int i = 0; i < PARTICLE_MAX; i++) {
		_particles[i]->Draw();
	}
}

void ExplosionEmitter::Emit(Vector2<float> Pos){
	_aliveFlag = true;
	for (int i = 0; i < PARTICLE_MAX; i++) {
		_particles[i]->Emit(Pos);
	}
}
