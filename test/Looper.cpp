#include "Looper.h"
//ここに呼び出したいシーンをinclude
#include "TitleScene.h"
#include "SelectScene.h"
#include "TestScene.h"
#include "GameScene.h"
using namespace std;

Looper::Looper() {
	//リソース読み込み
	Parameter parameter;
	_sceneStack.push(make_shared<TitleScene>(this, parameter));	//タイトル画面をスタックに入れる
}

bool Looper::loop() {
	//keyboard等の情報アップデート
	_sceneStack.top()->update();	//スタックの一番上を更新
	_sceneStack.top()->draw();		//スタックの一番上を描画
	_fps.wait();

	return true;
}


void Looper::onSceneChanged(const Scenes scene, const Parameter &parameter, const bool stackClear) {
	if(!_sceneStack.empty()) {
		
	}
	if (stackClear == true) {				//スタックをクリアする設定なら
		while (!_sceneStack.empty()) {		//スタックがからになるまでポップする
			_sceneStack.pop();
		}
	}
	switch (scene) {
	case Title:
		_sceneStack.push(make_shared<TitleScene>(this, parameter));
		break;

	case Select:
		_sceneStack.push(make_shared<SelectScene>(this, parameter));
		break;

	case Test1:
		_sceneStack.push(make_shared<TestScene>(this, parameter));
		break;

	case Game:
		_sceneStack.push(make_shared<GameScene>(this, parameter));
		break;
	default:
		//存在しないシーンがスタックトップにある際のエラー処理
		break;
	}
	_sceneStack.top()->init();
}

void Looper::sceneStackPop() {
	_sceneStack.pop();
}
