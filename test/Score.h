#pragma once
#include"Vector2.h"
#include"DxLib.h"

//点数とクリアタイム
class Score {
public:

	Score();

	void Initialize();
	void Finalize();

	//主に時間計測
	//参照渡し
	void Update(int &counter);

	//演出を考える必要あり
	void Draw() const;

	void Add();
	//念のため
	void Sub();

	void SetStopTimer();

private:

	Vector2<float> _scorePos, _iniScorePos;

	static int _point;

	int _scorePoint;
	int _secondTimer, _minutesTimer, _timer;

	bool _timerStartFlag;

};