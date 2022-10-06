#pragma once
#include "Scenes.h"
#include "Parameter.h"

class IoChangedListener {
public:
	IoChangedListener() = default;
	virtual	~IoChangedListener() = default;
	//•K‚¸ŽÀ‘•‚·‚é‚à‚Ì
	virtual void onSceneChanged(const Scenes scene, const Parameter &parameter,
		const bool stackClear) = 0;
	virtual void onSceneChanged(const Scenes scene, const Parameter& parameter1,
								const Parameter& parameter2, const bool stackClear) = 0;
	virtual void sceneStackPop() = 0;
};