#include "DxLib.h"
#include "SystemMain.h"
#include "Looper.h"
#include"WindowSize.h"

//DXライブラリの初期化
bool SystemMain::init() const {
	//SetWindowIconID(101);							//ウィンドウアイコン
	ChangeWindowMode(TRUE);							//ウィンドウモードに設定
	SetMainWindowText("TITLE");				//ウィンドウタイトル
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);	//サイズ変更不可
	SetWindowSizeExtendRate(1.0);					//画面サイズを設定（解像度との比率で設定）
	SetGraphMode(GetWinSize().x, GetWinSize().y, 32);		//画面サイズの最大サイズ、カラービット数を設定
	SetAlwaysRunFlag(TRUE);							//非アクティブ状態でも実行
	SetFontSize(32);								//フォントサイズ変更

	if (DxLib_Init() == -1) {						//初期化に失敗したら終了する

		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

//ゲームの終了処理
void SystemMain::end() const {
	DxLib_End();									//Dxライブラリ終了処理
}

//メイン処理
void SystemMain::main() const {
	Looper looper;
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!looper.loop()) {
			break;
		}
	}
}