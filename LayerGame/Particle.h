#pragma once
#include"Vector2.h"

class ParticleInfoTranser {
public:
	virtual ~ParticleInfoTranser() {};
	virtual void EmitterDead() = 0;
};

class Particle{
public:
	const enum BLEND_MODE {
		ALPHA, ADD
	};

protected:
	static const int BLEND[2];

	int _maxSpeed;			//�ő啬�o���x
	Vector2<float> _pos;	//���W
	Vector2<float> _vel;	//�ړ���
	float _size;			//�T�C�Y
	float _pal;				//�s�����x
	int _palChange;

	BLEND_MODE _blendMode;

	bool _isAliveFlag;

	ParticleInfoTranser* _mTranser;

public:
	virtual ~Particle() {};

	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Draw() = 0;

	virtual void Emit(Vector2<float> initPos) = 0;

	bool GetAlive() { return _isAliveFlag; }
};

//�T�C�Y�ύX�Ȃ��A�l�p��`��,�����Ȃ�
class BoxParticle :public Particle{

protected:
	int _red;
	int _green;
	int _blue;

public:
	BoxParticle(ParticleInfoTranser* Transer,int initSize, int maxEmitSpeed, int palChangeRate, BLEND_MODE blend, int r, int g, int b);
	~BoxParticle() {};

	virtual void Initialize()override;
	virtual void Draw()override;
	virtual void Emit(Vector2<float> initPos)override;
};

//�T�C�Y�ύX�Ȃ��A�l�p��`��,��������
class FallBoxParticle :public BoxParticle{
	float _gravity;
	float _fallVel;

public:
	FallBoxParticle(ParticleInfoTranser* Transer, int initSize, int maxEmitSpeed, int palChangeRate, BLEND_MODE blend, int r, int g, int b, float gravity);
	virtual void Update()override;
	virtual void Emit(Vector2<float>initPos)override;
};

//�T�C�Y�ύX����A�摜��`��A�����Ȃ��A�C�[�W���O
class ExplosionParticle :public Particle {

	static const int GRAPH_SIZE = 32;
	static const int GRAPH_TYPE = 3;
	static int GRAPH[GRAPH_TYPE];
	static const float SPIN_SPEED;
	Vector2<float> _maxVel;
	float _changeRate;
	float _rateChangeSpeed;
	float _maxSize;
	int* _graph;
	float _angle;
	float _ease;

public:
	ExplosionParticle(ParticleInfoTranser* Transer, int InitSize, int MaxEmitSpeed, float ChangeRate, BLEND_MODE Blend);
	~ExplosionParticle() {};

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Emit(Vector2<float> initPos)override;
};