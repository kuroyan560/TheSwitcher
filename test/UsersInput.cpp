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

void InputUpdate()
{
	//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
	for (int i = 0; i < KEY_NUM; i++)
		oldkeys[i] = keys[i];

	//最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

bool JustInput(int KeyCode)
{
	if (keys[KeyCode] && !oldkeys[KeyCode])return true;
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
