#include "Score.h"

int Score::_point = 10;

Score::Score() {

	_scorePoint = 0;
	_scorePos = { 500,600 };

	_iniScorePos = _scorePos;

	_secondTimer = -1;
	_minutesTimer = 0;


	_timerStartFlag = true;
}

void Score::Initialize() {

	_scorePoint = 0;

	_iniScorePos;

	_secondTimer = -1;
	_minutesTimer = 0;

	_timerStartFlag = true;
}

void Score::Finalize() {
}

void Score::Update(int &counter) {

	if (_timerStartFlag) {

		if (counter % 60 == 0) {

			_secondTimer++;

		}

		if (_secondTimer >= 60) {

			_minutesTimer++;
			_secondTimer = 0;

		}
	}
}

void Score::Draw() const {

	DrawFormatString(_scorePos.x, _scorePos.y, GetColor(255, 255, 255), "MinutesTimer%d,SecondTimer%d,Timer%d", _minutesTimer, _secondTimer + 1, _timer);
	DrawFormatString(_scorePos.x, _scorePos.y + 30, GetColor(255, 255, 255), "ScorePoint%d", _scorePoint);

}

void Score::Add() {

	_scorePoint += _point;

}

void Score::Sub() {

	_scorePoint += -_point;

}

void Score::SetStopTimer() {

	_timerStartFlag = false;

}