#pragma once
#include"Vector2.h"
#include"DxLib.h"

//�_���ƃN���A�^�C��
class Score {
public:

	Score();

	void Initialize();
	void Finalize();

	//��Ɏ��Ԍv��
	//�Q�Ɠn��
	void Update(int &counter);

	//���o���l����K�v����
	void Draw() const;

	void Add();
	//�O�̂���
	void Sub();

	void SetStopTimer();

private:

	Vector2<float> _scorePos, _iniScorePos;

	static int _point;

	int _scorePoint;
	int _secondTimer, _minutesTimer, _timer;

	bool _timerStartFlag;

};