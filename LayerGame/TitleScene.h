#pragma once
#include "AbstractScene.h"

class TitleScene : public AbstractScene {
private:
	int _graph;
public:
	TitleScene(IoChangedListener *impl, const Parameter &parameter,Fade* Fader,GoalEffect* GoalEffecter);
	virtual ~TitleScene() = default;
	void init() override;
	void finalize() override;
	void update() override;
	void draw()override;
};