#include "TestScene.h"
#include "DxLib.h"
#include"WindowSize.h"

TestScene::TestScene(IoChangedListener *impl, const Parameter &parameter)
	: AbstractScene(impl, parameter){
	/*player(Player::DIRECTION_LEFT),
	camera(GetWinSize()) */
	counter = 0;
	second = 0;
}

void TestScene::init() {
}

void TestScene::finalize() {
}


void TestScene::update() {
}

void TestScene::draw() const {
	
}
