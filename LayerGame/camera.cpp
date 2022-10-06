#include "camera.h"
#include"UsersInput.h"
#include"DxLib.h"
#include"WindowSize.h"
#include"easing.h"

const float Camera::CHANGE_RATE = 0.009F;
const float Camera::SCROLL_CHANGE_RATE = 0.013F;

Camera::Camera(){
}

Camera::~Camera(){
}

void Camera::Init(const int MaxStageNum, const int NowStage){
	posX = (MaxStageNum - 1) * GetWinSize().x;
	oldPosX = posX;
	toX = NowStage * GetWinSize().x;
	if (NowStage != MaxStageNum - 1) {
		rate = 0.0F;
		firstScroll = false;
	}
	else {
		rate = 1.0F;
		firstScroll = true;
	}
}

void Camera::Update() {

	if (rate < 1.0F) {

		if (firstScroll) {
			rate += CHANGE_RATE;
		}
		else {
			rate += SCROLL_CHANGE_RATE;
		}
		if (1.0F < rate) {
			rate = 1.0F;
			firstScroll = true;
		}
	}

	if (firstScroll) {
		posX = (toX - oldPosX) * Ease(InOut, Quad, rate) + oldPosX;
	}
	else {
		posX = (toX - oldPosX) * Ease(Out, Exp, rate) + oldPosX;
	}
}

bool Camera::NowScroll()
{
	if (rate != 1.0F) {
		return true;
	}
	else return false;
}

bool Camera::CanInputSelect()
{
	if (0.4F < rate && firstScroll) {
		return true;
	}
	else return false;
}

void Camera::MoveSet(const int& NowSelect){
	oldPosX = posX;
	rate = 0.0F;
	toX = NowSelect * GetWinSize().x;
}
