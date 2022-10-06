#include "DxLib.h"
#include "SelectScene.h"
#include "UsersInput.h"
//�Z���N�g�V�[������ړ��ł���V�[��������΂�����include
#include "TestScene.h"
#include "GameScene.h"

SelectScene::SelectScene(IoChangedListener *impl, const Parameter &parameter)
    : AbstractScene(impl, parameter) {
}

void SelectScene::init()
{
}

void SelectScene::finalize()
{
}

void SelectScene::update() {
    InputUpdate();
    if (JustInput(KEY_INPUT_1)) {
        Parameter parameter;
        parameter.set(GameScene::StageTag,1);
        _implSceneChanged->onSceneChanged(Scenes::Game, parameter, false);
    }
    if (JustInput(KEY_INPUT_2)) {
        Parameter parameter;
        parameter.set(GameScene::StageTag, 2);
        _implSceneChanged->onSceneChanged(Scenes::Game, parameter, false);
    }
}

void SelectScene::draw() const {
    DrawStringF(0, 0, "�Z���N�g�V�[���ł�����\n1.�Q�[���`�F�b�N�p\n2.�p�����[�^�`�F�b�N�p\n3.2�����������z�ł�", GetColor(255, 255, 255));
}
