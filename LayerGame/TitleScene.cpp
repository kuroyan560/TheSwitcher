#include "DxLib.h"
#include "UsersInput.h"
#include "TitleScene.h"
#include"SoundEmitter.h"
//�^�C�g������ړ��ł���V�[��������΂�����include

TitleScene::TitleScene(IoChangedListener *impl, const Parameter &parameter,Fade* Fader, GoalEffect* GoalEffecter)
    : AbstractScene(impl, parameter,Fader, GoalEffecter) {
    _graph = LoadGraph("_resource/graphics/title.png");
}

void TitleScene::init(){
    PlayBGM(TITLE);
}

void TitleScene::finalize()
{
}

void TitleScene::update() {
    InputUpdate();
    if(JustInput(KEY_INPUT_SPACE)) {
        _mFader->TurnBlack();
    }
    if (JustInput(KEY_INPUT_UP)) {
        DxLib_End();
        exit(0);
    }

    if (_mFader->TurnBlackTrigger() == true) {
        StopBGM(TITLE);
        Parameter parameter;
        _implSceneChanged->onSceneChanged(Scenes::Select, parameter, false);
    }

}

void TitleScene::draw() {
    DrawGraph(0, 0, _graph, true);
    DrawStringF(0, 0, "�^�C�g���ł�����\nspace��������select��\n��������ƏI�����܂�����", GetColor(255, 255, 255));
}
