#pragma once
#include "AbstractScene.h"

class TitleScene : public AbstractScene {
public:
	TitleScene(IoChangedListener *impl, const Parameter &parameter);
	virtual ~TitleScene() = default;
	void init() override;
	void finalize() override;
	void update() override;
	void draw() const override;
};