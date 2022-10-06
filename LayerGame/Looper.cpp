#include "Looper.h"
//ここに呼び出したいシーンをinclude
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include"SoundEmitter.h"
using namespace std;

Looper::Looper() {
	//リソース読み込み
	Parameter parameter;
	_sceneStack.push(make_shared<TitleScene>(this, parameter,&_fader, &_goalEffect));	//タイトル画面をスタックに入れる
	_sceneStack.top()->init();
}

bool Looper::loop() {
	SoundUpdate();
	_sceneStack.top()->update();	//スタックの一番上を更新
	_fader.Update();
	_goalEffect.Update();
	_sceneStack.top()->draw();		//スタックの一番上を描画
	_fader.Draw();
	_goalEffect.Draw();

	return true;
}


void Looper::onSceneChanged(const Scenes scene, const Parameter &parameter, const bool stackClear) {
	_sceneStack.top()->finalize();

	if(!_sceneStack.empty()) {
		if (stackClear == true) {				//スタックをクリアする設定なら
			while (!_sceneStack.empty()) {		//スタックがからになるまでポップする
				_sceneStack.pop();
			}
		}
	}

	switch (scene) {
	case Title:
		_sceneStack.push(make_shared<TitleScene>(this, parameter, &_fader,&_goalEffect));
		break;

	case Select:
		_sceneStack.push(make_shared<SelectScene>(this, parameter, &_fader, &_goalEffect));
		break;

	case Game:
		_sceneStack.push(make_shared<GameScene>(this, parameter, &_fader, &_goalEffect));
		break;
	default:
		//存在しないシーンがスタックトップにある際のエラー処理
		break;
	}
	_sceneStack.top()->init();
}

void Looper::onSceneChanged(const Scenes scene, const Parameter& parameter1, const Parameter& parameter2, const bool stackClear)
{
	_sceneStack.top()->finalize();

	if (!_sceneStack.empty()) {

	}
	if (stackClear == true) {				//スタックをクリアする設定なら
		while (!_sceneStack.empty()) {		//スタックがからになるまでポップする
			_sceneStack.pop();
		}
	}
	switch (scene) {
		case Game:
			_sceneStack.push(make_shared<GameScene>(this, parameter1, parameter2, &_fader, &_goalEffect));
			break;
		default:
			//存在しないシーンがスタックトップにある際のエラー処理
			break;
	}
	_sceneStack.top()->init();
}

void Looper::sceneStackPop() {
	_sceneStack.pop();
	_sceneStack.top()->init();
}
