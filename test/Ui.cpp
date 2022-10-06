#include "Ui.h"

//ゴール地点設定
const float Ui::_GOAL_POS = 2500;
//UIの位置設定
const Vector2<float> Ui::_UI_POS = { 500,500 };
const Vector2<float> Ui::_UI_SIZE = { 25,100 };

Ui::Ui() {

	_plPos = { 0,0 };
	_nowPos = { 0,0 };

	_uiGraph = _plGraph = 0;

	if (!_plGraph) {

		LoadGraph("sample.png");

	}
	if (!_uiGraph) {

		LoadGraph("sample.png");

	}

}

void Ui::Initialize() {
	//プレイヤー側で行われる
}

void Ui::Finalize() {
	//特になし
}

void Ui::Update(Vector2<float> PlPos) {
	_plPos = -PlPos;
	if (_plPos.y >= _GOAL_POS) {

		_plPos.y = _GOAL_POS;

	}
	else if (0 >= _plPos.y) {

		_plPos.y = 0;

	}

	_nowPos.x = _UI_POS.x;
	_nowPos.y = (_UI_POS.y + _UI_SIZE.y) + -(_plPos.y / _GOAL_POS) * 100;

}

void Ui::Draw() const {

	//Ui
	if (!_uiGraph || _uiGraph == -1) {

		DrawBox(_UI_POS.x, _UI_POS.y, _UI_POS.x + _UI_SIZE.x, _UI_POS.y + _UI_SIZE.y, GetColor(255, 0, 0), TRUE);
	}
	else {

		DrawGraph(_UI_POS.x, _UI_POS.y, _uiGraph, TRUE);

	}

	//Pl
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 150);

	if (!_plGraph || _plGraph == -1) {

		DrawBox(_nowPos.x, _nowPos.y, _nowPos.x + 25, _nowPos.y + 25, GetColor(255, 255, 255), TRUE);

	}
	else {

		DrawGraph(_nowPos.x, _nowPos.y, _plGraph, TRUE);

	}

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

