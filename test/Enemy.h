#pragma once
#include<math.h>
#include<vector>
#include"DxLib.h"
#include"Vector2.h" 

typedef enum { UPDOWN, LEFTRIGHT, STOP }EnemyStatus;

class Enemy {
public:

	Enemy();

	void Initialize(int x, int y, int WPB, int HPB, EnemyStatus Status);
	void Finalize();

	void Update();
	void Draw(Vector2<float> CamPos) const;

	const Vector2<float> GetPos();
	void SetEneDead();

private:

	static const Vector2<float> MOVE_MAX;
	static const Vector2<float> MOVE_MIN;
	static const float MOVE_SPEED;
	static const int MOVEMENT;

	Vector2<float> _enePos, _moveVelocity;
	Vector2<float> _eneSize;

	Vector2<float>_moveCountVel;

	EnemyStatus _status;

	bool _isAliveFlag;

	float _count;

	static int _graph[4];


	int _timer;
	int _animationFlame;
	static int _animation_Max_Flame;
	static int _animation_Speed;

};

