#pragma once
#include <stack>
#include <memory>
#include "AbstractScene.h"
#include "IoChangedListener.h"
#include"Fade.h"
#include"Effect.h"

using namespace std;

class Looper final : public IoChangedListener {
public:
	Looper();
	~Looper() = default;
	bool loop();
	void onSceneChanged(const Scenes scene, const Parameter &parameter, const bool stackClear) override;
	void onSceneChanged(const Scenes scene, const Parameter& parameter1, const Parameter& parameter2, const bool stackClear) override;
	void sceneStackPop() override;

private:
	stack<shared_ptr<AbstractScene>> _sceneStack;	//シーンスタック
	Fade _fader;
	GoalEffect _goalEffect;
};

