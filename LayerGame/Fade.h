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

	//上の階層に向かう時にこの関数を使用
	void GoingDownFloor();
	//下の階層に向かう時にこの関数を使用
	void GoingUpFloor();
	//暗転する時に使用
	void TurnBlack();

	bool ChangeFloorTrigger();
	bool TurnBlackTrigger();

	bool NowFadeFlag();

private:
	//シーンチェンジ
	Vector2<float> _downScenePos, _upScenePos, _sceneVelocity;
	bool _upSceneChangeFlag, _downSceneChangeFlag;
	int _sceneGraph;
	bool _upDownScreenAllBlackFlag;
	bool _turnAllBlackScreenFlag;
	Vector2<float> _sceneSize;

	//暗転
	Vector2<float>_boxPos, _boxSize;
	int _alpha;

	bool _startTurnDarkFlag;
	bool _gettingDarkFlag;
	static const int ALPHA_SPEED;

	int _timer;
	bool _stopTimerFlag;

	bool _;


	//ステージ切り替え
	void UpdateChangeFloor();
	//暗転
	void UpdateSceneChange();

	void DrawChangeFloor()const;
	void DrawSceneChange()const;

};

