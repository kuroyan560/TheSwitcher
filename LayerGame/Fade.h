#pragma once
#include"Vector2.h"
#include"DxLib.h"

class Fade {
public:

	Fade();

	void Initialize();
	void Finalize();

	void Update();


	void Draw()const;

	//��̊K�w�Ɍ��������ɂ��̊֐����g�p
	void GoingDownFloor();
	//���̊K�w�Ɍ��������ɂ��̊֐����g�p
	void GoingUpFloor();
	//�Ó]���鎞�Ɏg�p
	void TurnBlack();

	bool ChangeFloorTrigger();
	bool TurnBlackTrigger();

	bool NowFadeFlag();

private:
	//�V�[���`�F���W
	Vector2<float> _downScenePos, _upScenePos, _sceneVelocity;
	bool _upSceneChangeFlag, _downSceneChangeFlag;
	int _sceneGraph;
	bool _upDownScreenAllBlackFlag;
	bool _turnAllBlackScreenFlag;
	Vector2<float> _sceneSize;

	//�Ó]
	Vector2<float>_boxPos, _boxSize;
	int _alpha;

	bool _startTurnDarkFlag;
	bool _gettingDarkFlag;
	static const int ALPHA_SPEED;

	int _timer;
	bool _stopTimerFlag;

	bool _;


	//�X�e�[�W�؂�ւ�
	void UpdateChangeFloor();
	//�Ó]
	void UpdateSceneChange();

	void DrawChangeFloor()const;
	void DrawSceneChange()const;

};

