#include "Effect.h"
#include"SoundEmitter.h"

//コピー演出==============================================================

const int CopyEffect::_ANIMATION_MAX_TIMER = 10;
int CopyEffect::_flashGraph = 0;

CopyEffect::CopyEffect() {
	if (!_flashGraph) {

		_flashGraph = LoadGraph("_resource/graphics/CopyLight.png");

	}
}

void CopyEffect::Initialize(const Vector2<int> PosNum, const float& Size) {

	//フラッシュ
	_decreFlashFlag = false;

	_flash = 255;
	_flashPos.x = (float)(PosNum.x) * Size;
	_flashPos.y = (float)(PosNum.y) * Size;
	_size = Size;
	_startFlashFlag = true;

	_count = 1;
}

void CopyEffect::Update() {

	if (_flash >= 255) {

		_decreFlashFlag = true;

	}
	else if (_flash <= 170) {

		_decreFlashFlag = false;

	}

	if (_decreFlashFlag) {

		_flash -= 5;

	}
	else {

		_flash += 5;

	}

	if (_count >= 2) {

		_startFlashFlag = false;

	}

}

void CopyEffect::Draw() const {
	if (_startFlashFlag) {

		SetDrawBlendMode(DX_BLENDMODE_ADD, _flash);
		//DrawGraph(_flashPos.x, _flashPos.y, _flashGraph, TRUE);
		DrawExtendGraph(_flashPos.x, _flashPos.y, _flashPos.x + _size, _flashPos.y + _size, _flashGraph, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//ゴール演出==============================================================

int GoalEffect::_clearFontGraph[5] = { 0,0,0,0,0 };

GoalEffect::GoalEffect() {

	if (!_clearFontGraph[0]) {

		LoadDivGraph("_resource/graphics/CLEARfont.png", 5, 5, 1, 64, 64, _clearFontGraph, TRUE);

	}

}

void GoalEffect::Initialize() {

	//ゴール
	_goalPos = { 0,0 };
	_goalTimer = 0;
	_goalR = 0;
	_goal2R = 0;

	_startAlphaFlag = false;

	for (int i = 0; i < 5; i++) {

		_fontPos[i] = { 350 + i * 128.0F,0 };
		_fontTimer[i] = 0;
		_startTimerFlag[i] = false;

	}

	_fTimer = 0;
	_allTimer = 0;

	_alpha = 255;

	_shrinkFlag = false;
	_startGoalFlag = false;

	_fontDisappearFlag = false;

	_shrinkGoalPos = { 0,0 };
	

}

void GoalEffect::Update() {
	if (_startGoalFlag) {

		//ゴールシーン拡大
		if (_goalTimer <= 2.0F) {

			_goalTimer += 0.01F;

		}
		if (_goalTimer >= 1.5F) {

			_goalTimer = 1.5F;

			_fTimer++;
			_startAlphaFlag = true;

		}

		if (_alpha < 0) {

			_shrinkFlag = true;

		}

		//シーン縮小
		if (_shrinkFlag) {

			_sceneShrink += 0.01F;

		}
		if (_sceneShrink > 1.0F) {

			_sceneShrink = 1.0F;

		}


		if (_fTimer > 120) {

			_alpha -= 10;

		}
		if (_startAlphaFlag) {

			_allTimer++;

		}

		//フォントが消える瞬間
		if (_alpha <= 0) {

			_fontDisappearFlag = true;

		}


		//フォント
		for (int i = 0; i < 5; i++) {

			if (_allTimer >= 10 + i * 10) {

				_startTimerFlag[i] = true;

			}

			if (_startTimerFlag[i] && 1.0F > _fontTimer[i]) {

				_fontTimer[i] += 0.05F;

			}
			else if (_startTimerFlag[i] && 2.0F < _fontTimer[i]) {

				_fontTimer[i] = 2.0F;
				_startTimerFlag[i] = true;

			}

			_fontPos[i].y = -100 + Ease(Out, Cubic, _fontTimer[i]) * 350;

		}


		if (!_shrinkFlag) {

			_goalR += Ease(In, Elastic, _goalTimer) * 5;
			_goal2R = _goalR;

		}
		else {

			_goal2R -= Ease(Out, Elastic, _sceneShrink) * 30;

			if (_goal2R <= 0) {

				_startGoalFlag = false;

			}
		}


		if (_goalR > 1200) {

			_goalR = 1200;

		}

	}

}

void GoalEffect::Draw() const {

	if (_startGoalFlag) {

		if (!_shrinkFlag) {

			DrawCircle(_goalPos.x, _goalPos.y, _goalR, GetColor(255, 255, 255), TRUE);

		}
		else {

			DrawCircle(_shrinkGoalPos.x, _shrinkGoalPos.y, _goal2R, GetColor(255, 255, 255), TRUE);

		}


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		for (int i = 0; i < 5; i++) {

			DrawGraph(_fontPos[i].x, _fontPos[i].y, _clearFontGraph[i], TRUE);

		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

void GoalEffect::ReachToGoal(const Vector2<float> GoalPos, const Vector2<float> shrinkGoalPos) {

	_goalPos = GoalPos;
	_shrinkGoalPos = shrinkGoalPos;

	_startGoalFlag = true;

}

bool GoalEffect::FontDisappearTrigger() {

	return _fontDisappearFlag;

}
