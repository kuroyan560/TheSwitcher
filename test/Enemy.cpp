#include "Enemy.h"
//#include"WallAndFloor.h"
//#include"WindowSize.h"
int Enemy::_graph[] = { 0 };

const Vector2<float> Enemy::MOVE_MAX = { 300,300 };
const float Enemy::MOVE_SPEED = 5;

const int Enemy::MOVEMENT = 70;

int Enemy::_animation_Max_Flame = 4;
int Enemy::_animation_Speed = 60;

Enemy::Enemy() {


	_enePos = { 0,0 };

	_eneSize = { 25,25 };

	_isAliveFlag = false;

	_moveVelocity = { 0,0 };
	_moveCountVel = { 0,0 };

	_animationFlame = 0;
	_timer = 0;

	_count = 0;

	if (!_graph[0]) { LoadDivGraph("AnimationCheck.png", 4, 4, 1, 32, 32, _graph, FALSE); }

}

void Enemy::Initialize(int x, int y, int WPB, int HPB, EnemyStatus Status) {

	//_enePos = { (float)(x * WPB + WallAndFloor::WALL_WIDTH - WallAndFloor::SPEAR_WIDTH)
	//,(float)(-y * HPB + GetWinSize().y - WallAndFloor::FLOOR_HEIGHT) };

	_isAliveFlag = true;

	_status = Status;

	_animationFlame = 0;
	_timer = 0;

	_count = 0;
}

void Enemy::Finalize() {

	_isAliveFlag = false;
	//DeleteGraph(_graph[0]);

}

//Eneの動きと生存、死亡時の処理
void Enemy::Update() {

	if (_isAliveFlag) {

		//最初下から移動する
		if (_status == UPDOWN) {

			_count--;
			_moveVelocity.y = -(sin(DX_PI / 2 / MOVEMENT * _count) * 2);

		}
		else if (_status == LEFTRIGHT) {

			_count--;
			_moveVelocity.x = -(sin(DX_PI / 2 / MOVEMENT * _count) * 2);

		}
		else if (_status == STOP) {



		}

	}
	//死亡時
	else {}



	_timer++;

	if (_timer > _animation_Speed && _animationFlame < _animation_Max_Flame) {

		_animationFlame++;
		_timer = 0;

	}
	if (_animationFlame >= _animation_Max_Flame) {

		_animationFlame = 0;

	}


	_enePos += _moveVelocity;
}

//画像を使用してない場合、Boxで描画、使用している場合は画像を描画する
void Enemy::Draw(Vector2<float> CamPos) const{

	if (_isAliveFlag) {

		if (!_graph || _graph[0] == -1) { 
			
			DrawBox(_enePos.x - CamPos.x, _enePos.y - CamPos.y, _enePos.x + _eneSize.x - CamPos.x, _enePos.y + _eneSize.y - CamPos.y, GetColor(255, 255, 255), TRUE); 
		
		}
		else { 

			DrawGraph(_enePos.x - CamPos.x, _enePos.y - CamPos.y, _graph[_animationFlame], TRUE); 

		}

	}
}

inline const Vector2<float> Enemy::GetPos() {

	return _enePos;

}

void Enemy::SetEneDead() {

	_isAliveFlag = false;

}