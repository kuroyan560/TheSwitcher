#pragma once
#include"Vector2.h"
#include"Camera.h"
class Player {
private:
//��{���i�萔�j
	//�v���C���[�̃T�C�Y
	static const Vector2<float> SIZE;

	//�e���[�v�A�j���[�V�����摜�p�X
	static const char* WAIT_GRAPH_PASS;
	static const char* JUMP_GRAPH_PASS;
	static const char* WALL_GRAPH_PASS;
	static const char* STEP_ENEMY_GRAPH_PASS;
	static const char* SMALL_JUMP_GRAPH_PASS;

	//�e���[�v�A�j���[�V�����ő�t���[����
	static const int WAIT_FLAME_MAX = 1;
	static const int JUMP_FLAME_MAX = 2;
	static const int WALL_FLAME_MAX = 2;
	static const int STEP_ENEMY_FLAME_MAX = 5;		//�Ō�̂P�t���[���͋�

	//�e���[�v�A�j���[�V�����̑����i�l���傫���قǒx���Ȃ�j
	static const int WAIT_MOTION_SPEED = 15;
	static const int JUMP_MOTION_SPEED = 5;
	static const int WALL_MOTION_SPEED = 5;
	static const int STEP_ENEMY_MOTION_SPEED = 4;

	static const int INPUT_FLAME_RANGE = 4;	//�W�����v���͔���̋��e�t���[���͈�

	//�P�����Ƃ���������Ƃ�t���[���͈�
	static const int SHORT_PRESS_FLAME = 10;

	//���W�����v�����ω����x
	static const float SMALL_JUMP_CHANGE_RATE;

	//���W�����v�A���łł����
	static const int SMALL_JUMP_COUNT_MAX = 4;

	//���藎���̑���
	//static const int MAX_FALL_SPEED = 6;
	//static const float FALL_RATE_CHANGE;

	//�ő�HP
	static const int MAX_HP = 3;

public:
//�����񋓑�
	enum Direction { DIRECTION_LEFT = -1, DIRECTION_RIGHT = 1 };

private:
//�摜�Ɋւ���
	//�摜�n���h��
	int _graphWait[WAIT_FLAME_MAX];				//�ҋ@
	int _graphJump[JUMP_FLAME_MAX];				//�W�����v
	int _graphWall[WALL_FLAME_MAX];				//�ǂ͂��
	int _graphStepEnemy[STEP_ENEMY_FLAME_MAX];	//�G���݂�
	int _graphSmallJump;						//���W�����v

	//�摜���ǂ���������
	Direction _graphDirection;

	int* _graph;
	const int* _flameMax;
	const int* _motionSpeed;

	//���[�v�A�j���[�V�����p
	int _flame;

//���W�E�ړ��Ɋւ���
	//���W
	Vector2<float> _pos;
	//�ړ���
	Vector2<float> _move;
	//�W�����v����move
	Vector2<float> _jumpSpeed;
	//�����X�s�[�h
	float _fallSpeed;
	//����
	int _nowDirection;
	int _moveDirection;

	//�ǂ͂�����̗������x�ω���
	float _fallChangeRate;
	bool _oldStickWall;

	//�̗͂Ɋւ���
	int _hp;

	//�G���݂����[�V����
	bool _stepFlag;

	//�{�^���������
	int _pressFlame;

	//���W�����v�ɂ���
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

	//�ǂƓ����蔻�肠��Ƃ�
	void StickWall(int Which,int WallSpear, int WallWidth, int WindowWidth);	//���c0�A�E�c1
	//���Ɠ����蔻�肠��Ƃ�
	void GroundFloor(int FloorHeight,int WindowHeight, int FPB, int NowFlame);

	Vector2<float> GetPos()const { return _pos; }
	Vector2<float> GetSize()const { return SIZE; }
	float GetCanJumpSizeX()const;

	void Jump(int FPB, int NowFlame,Camera &cameraObj);
	void SmallJump(int FPB, int NowFlame);

	//�G�̓��݂�
	void StepEnemy(int FPB, int NowFlame);

	void Damaged();

	void Dead();

	int GetSmallJumpCount() { return _smallJumpCount; }
};