#pragma once
#include"Vector2.h"
#include"Camera.h"
class Player {
private:
//基本情報（定数）
	//プレイヤーのサイズ
	static const Vector2<float> SIZE;

	//各ループアニメーション画像パス
	static const char* WAIT_GRAPH_PASS;
	static const char* JUMP_GRAPH_PASS;
	static const char* WALL_GRAPH_PASS;
	static const char* STEP_ENEMY_GRAPH_PASS;
	static const char* SMALL_JUMP_GRAPH_PASS;

	//各ループアニメーション最大フレーム数
	static const int WAIT_FLAME_MAX = 1;
	static const int JUMP_FLAME_MAX = 2;
	static const int WALL_FLAME_MAX = 2;
	static const int STEP_ENEMY_FLAME_MAX = 5;		//最後の１フレームは空

	//各ループアニメーションの速さ（値が大きいほど遅くなる）
	static const int WAIT_MOTION_SPEED = 15;
	static const int JUMP_MOTION_SPEED = 5;
	static const int WALL_MOTION_SPEED = 5;
	static const int STEP_ENEMY_MOTION_SPEED = 4;

	static const int INPUT_FLAME_RANGE = 4;	//ジャンプ入力判定の許容フレーム範囲

	//単押しという判定をとるフレーム範囲
	static const int SHORT_PRESS_FLAME = 10;

	//小ジャンプ完了変化速度
	static const float SMALL_JUMP_CHANGE_RATE;

	//小ジャンプ連続でできる回数
	static const int SMALL_JUMP_COUNT_MAX = 4;

	//ずり落ちの速さ
	//static const int MAX_FALL_SPEED = 6;
	//static const float FALL_RATE_CHANGE;

	//最大HP
	static const int MAX_HP = 3;

public:
//向き列挙体
	enum Direction { DIRECTION_LEFT = -1, DIRECTION_RIGHT = 1 };

private:
//画像に関して
	//画像ハンドル
	int _graphWait[WAIT_FLAME_MAX];				//待機
	int _graphJump[JUMP_FLAME_MAX];				//ジャンプ
	int _graphWall[WALL_FLAME_MAX];				//壁はりつき
	int _graphStepEnemy[STEP_ENEMY_FLAME_MAX];	//敵踏みつけ
	int _graphSmallJump;						//小ジャンプ

	//画像がどちら向き基準か
	Direction _graphDirection;

	int* _graph;
	const int* _flameMax;
	const int* _motionSpeed;

	//ループアニメーション用
	int _flame;

//座標・移動に関して
	//座標
	Vector2<float> _pos;
	//移動量
	Vector2<float> _move;
	//ジャンプ中のmove
	Vector2<float> _jumpSpeed;
	//落下スピード
	float _fallSpeed;
	//向き
	int _nowDirection;
	int _moveDirection;

	//壁はりつき時の落下速度変化率
	float _fallChangeRate;
	bool _oldStickWall;

	//体力に関して
	int _hp;

	//敵踏みつけモーション
	bool _stepFlag;

	//ボタン押下情報
	int _pressFlame;

	//小ジャンプについて
	float _smallJumpRate;
	float _oldY;
	float _toY;
	int _smallJumpCount;

	void JumpGround(int FPB, int NowFlame);

public:
	Player(Direction GraphDirection);
	~Player();

	void Initialize(Vector2<float>WindowSize, int FloorHeight,int WallBetweenWalls,int FPB,float HPB);
	void Finalize();
	void Update(int FPB, int NowFlame);
	void Draw(const Vector2<float>&CamScroll) const;

	bool TriggerTouchWall();

	//壁と当たり判定あるとき
	void StickWall(int Which,int WallSpear, int WallWidth, int WindowWidth);	//左…0、右…1
	//床と当たり判定あるとき
	void GroundFloor(int FloorHeight,int WindowHeight, int FPB, int NowFlame);

	Vector2<float> GetPos()const { return _pos; }
	Vector2<float> GetSize()const { return SIZE; }
	float GetCanJumpSizeX()const;

	void Jump(int FPB, int NowFlame,Camera &cameraObj);
	void SmallJump(int FPB, int NowFlame);

	//敵の踏みつけ
	void StepEnemy(int FPB, int NowFlame);

	void Damaged();

	void Dead();

	int GetSmallJumpCount() { return _smallJumpCount; }
};