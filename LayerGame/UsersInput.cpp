#include "UsersInput.h"
#include"DxLib.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

const static int KEY_NUM = 256;
static char keys[KEY_NUM];		//最新のキーボード情報用
static char oldkeys[KEY_NUM];	//1ループ（フレーム）前のキーボード情報
static int inputFlame[4];      //上下左右長押し対応

static const int INPUT_FLAME = 13;
static const int SPACE_INPUT_FLAME = 120;

void InputUpdate()
{
	//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
	for (int i = 0; i < KEY_NUM; i++)
		oldkeys[i] = keys[i];

	//最新のキーボード情報を取得
	GetHitKeyStateAll(keys);

	//長押しカウント
	if (keys[KEY_INPUT_UP]) {
		inputFlame[MOVE_UP]++;
	}
	else {
		inputFlame[MOVE_UP] = 0;
	}
	if (keys[KEY_INPUT_DOWN]) {
		inputFlame[MOVE_DOWN]++;
	}
	else {
		inputFlame[MOVE_DOWN] = 0;
	}
	if (keys[KEY_INPUT_LEFT]) {
		inputFlame[MOVE_LEFT]++;
	}
	else {
		inputFlame[MOVE_LEFT] = 0;
	}
	if (keys[KEY_INPUT_RIGHT]) {
		inputFlame[MOVE_RIGHT]++;
	}
	else {
		inputFlame[MOVE_RIGHT] = 0;
	}
}

bool JustInput(int KeyCode)
{
	if (keys[KeyCode] && !oldkeys[KeyCode]) {
		return true;
	}
	else return false;
}

bool Input(int KeyCode)
{
	if (keys[KeyCode])return true;
	else return false;
}

bool JustOut(int KeyCode)
{
	if (!keys[KeyCode] && oldkeys[KeyCode])return true;
	else return false;
}

bool Press(int KeyCode)
{
	if (KeyCode == KEY_INPUT_UP) {
		if (JustInput(KEY_INPUT_UP)==true || INPUT_FLAME < inputFlame[MOVE_UP]) {
			return true;
		}
		else return false;
	}
	else if (KeyCode == KEY_INPUT_DOWN) {
		if (JustInput(KEY_INPUT_DOWN)==true || INPUT_FLAME < inputFlame[MOVE_DOWN]) {
			return true;
		}
		else return false;
	}
	else if (KeyCode == KEY_INPUT_LEFT) {
		if (JustInput(KEY_INPUT_LEFT) == true || INPUT_FLAME < inputFlame[MOVE_LEFT]) {
			return true;
		}
		else return false;
	}
	else if (KeyCode == KEY_INPUT_RIGHT) {
		if (JustInput(KEY_INPUT_RIGHT) == true || INPUT_FLAME < inputFlame[MOVE_RIGHT]) {
			return true;
		}
		else return false;
	}
	else return false;
}