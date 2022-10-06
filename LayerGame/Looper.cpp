#include "Looper.h"
//�����ɌĂяo�������V�[����include
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include"SoundEmitter.h"
using namespace std;

Looper::Looper() {
	//���\�[�X�ǂݍ���
	Parameter parameter;
	_sceneStack.push(make_shared<TitleScene>(this, parameter,&_fader, &_goalEffect));	//�^�C�g����ʂ��X�^�b�N�ɓ����
	_sceneStack.top()->init();
}

bool Looper::loop() {
	SoundUpdate();
	_sceneStack.top()->update();	//�X�^�b�N�̈�ԏ���X�V
	_fader.Update();
	_goalEffect.Update();
	_sceneStack.top()->draw();		//�X�^�b�N�̈�ԏ��`��
	_fader.Draw();
	_goalEffect.Draw();

	return true;
}


void Looper::onSceneChanged(const Scenes scene, const Parameter &parameter, const bool stackClear) {
	_sceneStack.top()->finalize();

	if(!_sceneStack.empty()) {
		if (stackClear == true) {				//�X�^�b�N���N���A����ݒ�Ȃ�
			while (!_sceneStack.empty()) {		//�X�^�b�N������ɂȂ�܂Ń|�b�v����
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
		//���݂��Ȃ��V�[�����X�^�b�N�g�b�v�ɂ���ۂ̃G���[����
		break;
	}
	_sceneStack.top()->init();
}

void Looper::onSceneChanged(const Scenes scene, const Parameter& parameter1, const Parameter& parameter2, const bool stackClear)
{
	_sceneStack.top()->finalize();

	if (!_sceneStack.empty()) {

	}
	if (stackClear == true) {				//�X�^�b�N���N���A����ݒ�Ȃ�
		while (!_sceneStack.empty()) {		//�X�^�b�N������ɂȂ�܂Ń|�b�v����
			_sceneStack.pop();
		}
	}
	switch (scene) {
		case Game:
			_sceneStack.push(make_shared<GameScene>(this, parameter1, parameter2, &_fader, &_goalEffect));
			break;
		default:
			//���݂��Ȃ��V�[�����X�^�b�N�g�b�v�ɂ���ۂ̃G���[����
			break;
	}
	_sceneStack.top()->init();
}

void Looper::sceneStackPop() {
	_sceneStack.pop();
	_sceneStack.top()->init();
}
