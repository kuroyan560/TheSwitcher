#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Camera.h"
#include "WallAndFloor.h"

class TestScene :public AbstractScene {
public:
	TestScene(IoChangedListener *impl, const Parameter &parameter);
	virtual ~TestScene() = default;
	void init() override;
	void finalize() override;
	void update() override;
	void draw() const override;

private:
	int counter;
	int second;
	/*Player player;
	Camera camera;
	WallAndFloor wallAndFloor;*/
};