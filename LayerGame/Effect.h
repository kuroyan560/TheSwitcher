#pragma once
#include"Vector2.h"
#include"DxLib.h"
#include"easing.h"

class CopyEffect {
private:
	static const int _ANIMATION_MAX_TIMER;
	//フラッシュ
	Vector2<float> _flashPos;
	float _size;

	bool _decreFlashFlag;
	int _flash;

	static int _flashGraph;

	bool _flashDrawGraph;
	bool _startFlashFlag;

	int _count;
public:
	CopyEffect();

	void Initialize(const Vector2<int> PosNum, const float& Size);
	void Update();
	void Draw()const;
	void TurnFalse() { _startFlashFlag = false; }

	void AddCount() { _count++; }
};

class GoalEffect {
public:
	GoalEffect();

	void Initialize();

	void Update();
	void Draw()const;

	//ゴールにたどり着いた際にこの関数を呼ぶ
	void ReachToGoal(const Vector2<float> GoalPos, const Vector2<float> shrinkGoalPos);

	//文字が消える瞬間
	bool FontDisappearTrigger();

	bool NowGoalEffect() { return _startGoalFlag; }

private:
	//クリア画面
	Vector2<float>_goalPos;
	float _goalTimer;
	float _goalR;
	float _goal2R;

	Vector2<float> _shrinkGoalPos;

	bool _startAlphaFlag;
	bool _returnFlag;

	int _alpha = 255;
	bool _startGoalFlag;

	Vector2<float> _fontPos[5];
	float _fontTimer[5];

	bool _startTimerFlag[5];
	float _allTimer;
	int _fTimer;


	float _sceneShrink = 0.0F;
	bool _shrinkFlag = false;

	bool _goalFlag;



	bool _fontDisappearFlag;


	static int _clearFontGraph[5];

};

