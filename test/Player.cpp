#include"DxLib.h"
#include "Player.h"
#include"UsersInput.h"
#include"easing.h"
#include"WallAndFloor.h"
const Vector2<float> Player::SIZE = { 64,64 };

const char* Player::WAIT_GRAPH_PASS = "player_wait.png";
const char* Player::JUMP_GRAPH_PASS = "player_jump.png";
const char* Player::WALL_GRAPH_PASS = "player_wall.png";
const char* Player::STEP_ENEMY_GRAPH_PASS = "player_step_enemy.png";
const char* Player::SMALL_JUMP_GRAPH_PASS = "player_small_jump.png";

const float Player::SMALL_JUMP_CHANGE_RATE = 0.05F;

Player::Player(Direction GraphDirection){
	LoadDivGraph(WAIT_GRAPH_PASS, WAIT_FLAME_MAX, WAIT_FLAME_MAX, 1, SIZE.x, SIZE.y, _graphWait);
	LoadDivGraph(JUMP_GRAPH_PASS, JUMP_FLAME_MAX, JUMP_FLAME_MAX, 1, SIZE.x, SIZE.y, _graphJump);
	LoadDivGraph(WALL_GRAPH_PASS, WALL_FLAME_MAX, WALL_FLAME_MAX, 1, SIZE.x, SIZE.y, _graphWall);
	LoadDivGraph(STEP_ENEMY_GRAPH_PASS, STEP_ENEMY_FLAME_MAX, STEP_ENEMY_FLAME_MAX, 1, SIZE.x, SIZE.y, _graphStepEnemy);
	_graphSmallJump = LoadGraph(SMALL_JUMP_GRAPH_PASS);

	_graphDirection = GraphDirection;
}

Player::~Player(){
}


void Player::Initialize(Vector2<float>WindowSize, int FloorHeight, int WallBetweenWalls, int FPB, float HPB){
	//待機アニメーション
	_graph = _graphWait;
	_flameMax = &WAIT_FLAME_MAX;
	_motionSpeed = &WAIT_MOTION_SPEED;
	_flame = 0;

	//座標は移動量、HPの初期化
	_move = { 0,0 };
	_jumpSpeed = { (float)(WallBetweenWalls / 5 / FPB),(float)-(HPB / FPB) };
	_pos = { (float)((WindowSize.x - WallBetweenWalls) / 2 + _jumpSpeed.x * FPB * 2),(float)WindowSize.y - FloorHeight - SIZE.y };
	_fallSpeed = HPB / FPB;
	_moveDirection = DIRECTION_LEFT;
	_fallChangeRate = 0.0F;
	_oldStickWall = false;

	_nowDirection = _graphDirection;

	_smallJumpRate = 1.0F;

	_hp = MAX_HP;

	_stepFlag = false;
}

void Player::Finalize(){
}

void Player::Update(int FPB, int NowFlame){
	//生存中
	if (0 < _hp){
		//アニメーションフレーム増加
		_flame++;

		//落下速度変化率増加
		/*if (fallChangeRate < 1.0F){
			fallChangeRate += FALL_RATE_CHANGE;

			if (1.0F < fallChangeRate){
				fallChangeRate = 1.0F;
			}
		}*/

		//移動量加算
		if (!_stepFlag)
		{
			_pos += _move;
		}
		else
		{
			if ((_flame / *_motionSpeed % *_flameMax) == *_flameMax - 1)
			{
				_graph = _graphJump;
				_flameMax = &JUMP_FLAME_MAX;
				_motionSpeed = &STEP_ENEMY_MOTION_SPEED;
				_pos += _move;
				_stepFlag = false;
			}
		}

		//小ジャンプ完了率増加
		if (_smallJumpRate < 1.0F) {
			_smallJumpRate += SMALL_JUMP_CHANGE_RATE;

			if (1.0F < _smallJumpRate) {
				_smallJumpRate = 1.0F;
			}
			_pos.y = (_oldY - _toY) * Ease(Out, Sine, _smallJumpRate) + _oldY;
		}
	}
	else
	{
		Dead();
	}
}

void Player::Draw(const Vector2<float>&CamScroll) const
{
	if (0 < _hp){
		if (_nowDirection == _graphDirection) {
			if (_smallJumpRate < 1.0F) {
				DrawGraph(_pos.x - CamScroll.x, _pos.y - CamScroll.y, _graphSmallJump, true);
			}
			else {
				DrawGraph(_pos.x - CamScroll.x, _pos.y - CamScroll.y, _graph[_flame / *_motionSpeed % *_flameMax], true);
			}
		}
		else {
			if (_smallJumpRate < 1.0F) {
				DrawTurnGraph(_pos.x - CamScroll.x, _pos.y - CamScroll.y, _graphSmallJump, true);
			}
			else {
				DrawTurnGraph(_pos.x - CamScroll.x, _pos.y - CamScroll.y, _graph[_flame / *_motionSpeed % *_flameMax], true);
			}
		}
	}
}

void Player::Jump(int FPB, int NowFlame, Camera& cameraObj)
{
	if (_pressFlame < SHORT_PRESS_FLAME) {
		for (int i = -INPUT_FLAME_RANGE; i <= INPUT_FLAME_RANGE; i++){
			if ((NowFlame + i) % FPB == 0){
				_nowDirection *= -1;
				_moveDirection *= -1;
				_move.x = _jumpSpeed.x * _moveDirection;
				_move.y = _jumpSpeed.y;
				_oldStickWall = false;

				//画像切替
				_graph = _graphJump;
				_flameMax = &JUMP_FLAME_MAX;
				_motionSpeed = &JUMP_MOTION_SPEED;

				//小ジャンプの回数リセット
				_smallJumpCount = 0;

				cameraObj.CamShake();

				break;
			}
		}
	}
}

void Player::SmallJump(int FPB, int NowFlame)
{
	//スペース押下情報保存
	if (JustInput(KEY_INPUT_SPACE) == true) {
		_pressFlame = 0;
	}
	else if (Input(KEY_INPUT_SPACE) == true) {
		_pressFlame++;

		if (SHORT_PRESS_FLAME <= _pressFlame && _smallJumpRate == 1.0F && NowFlame % FPB == 0 && _smallJumpCount < SMALL_JUMP_COUNT_MAX) {
			_smallJumpRate = 0.0F;
			_oldY = _pos.y;
			_toY = _pos.y - (_jumpSpeed.y * FPB);
			_smallJumpCount++;
		}
	}
}

void Player::JumpGround(int FPB, int NowFlame)
{
	if (JustOut(KEY_INPUT_SPACE) == true) {
		for (int i = -INPUT_FLAME_RANGE; i <= INPUT_FLAME_RANGE; i++)
		{
			if ((NowFlame + i) % FPB == 0)
			{
				_move.x = _jumpSpeed.x * _moveDirection;
				_move.y = _jumpSpeed.y;
				_oldStickWall = false;

				//画像切替
				_graph = _graphJump;
				_flameMax = &JUMP_FLAME_MAX;
				_motionSpeed = &JUMP_MOTION_SPEED;

				break;
			}
		}
	}
}

bool Player::TriggerTouchWall()
{
	//壁に触った瞬間
	if (_oldStickWall == false){
		//落下速度変化率のリセット
		_fallChangeRate = 0.0F;

		//画像切替
		_graph = _graphWall;
		_flameMax = &WALL_FLAME_MAX;
		_motionSpeed = &WALL_MOTION_SPEED;

		return true;
	}
	else return false;
}

void Player::StickWall(int Which, int WallSpear,int WallWidth, int WindowWidth){
	if (Which == 0){
		//左壁の押し戻し
		_pos.x = WallWidth-WallSpear;
		_move.x = 0.0F;
	}
	//右壁の押し戻し
	else if (Which == 1) {
		_pos.x = WindowWidth - WallWidth - SIZE.x+WallSpear;
		_move.x = 0.0F;
	}

	//壁に張りつき中
	//_move.y = Ease(In, Quad, fallChangeRate) * MAX_FALL_SPEED;
	_move.y = _fallSpeed;

	//前フレーム、壁にはりついていたという情報を保存
	_oldStickWall = true;

	//壁ジャンプ
	//Jump(FPB,NowFlame);

}

void Player::GroundFloor(int FloorHeight, int WindowHeight, int FPB, int NowFlame)
{
	_pos.y = WindowHeight - FloorHeight - SIZE.y;
	_move.y = 0.0F;

	JumpGround(FPB, NowFlame);
}

float Player::GetCanJumpSizeX() const
{
	return INPUT_FLAME_RANGE * _jumpSpeed.x;
}

void Player::StepEnemy(int FPB, int NowFlame)
{
	for (int i = -INPUT_FLAME_RANGE; i <= INPUT_FLAME_RANGE; i++)
	{
		if ((NowFlame + i) % FPB == 0)
		{
			_graph = _graphStepEnemy;
			_flameMax = &STEP_ENEMY_FLAME_MAX;
			_motionSpeed = &STEP_ENEMY_MOTION_SPEED;
			_stepFlag = true;
			break;
		}
	}
}

void Player::Damaged()
{
	_hp--;
}

void Player::Dead()
{
}