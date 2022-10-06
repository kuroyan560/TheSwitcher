#pragma once
#include "AbstractScene.h"

class SelectScene : public AbstractScene {
public:
	SelectScene(IoChangedListener *impl, const Parameter &parameter);
	virtual ~SelectScene() = default;
	void init() override;
	void finalize() override;
	void update() override;
	void draw() const override;
private:
	int _nowSlect;
};