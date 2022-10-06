#pragma once
#include "IoChangedListener.h"
#include "Parameter.h"
#include"Fade.h"
#include"Effect.h"

class IoChangedListener;

class AbstractScene {
protected:	//派生クラスのみアクセス可能
	IoChangedListener *_implSceneChanged;
	Fade* _mFader;
	GoalEffect* _mGoalEffecter;
public:
	AbstractScene(IoChangedListener* impl, const Parameter& parameter, Fade* Fader,GoalEffect* GoalEffecter);
	AbstractScene(IoChangedListener* impl, const Parameter& parameter1, const Parameter& parameter2, Fade* Fader, GoalEffect* GoalEffecter);
	virtual ~AbstractScene() = default;
	virtual void init() = 0;
	virtual void finalize() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

};

