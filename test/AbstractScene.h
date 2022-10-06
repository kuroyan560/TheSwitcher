#pragma once
#include "IoChangedListener.h"
#include "Parameter.h"

class IoChangedListener;

class AbstractScene {
protected:	//派生クラスのみアクセス可能
	IoChangedListener *_implSceneChanged;
public:
	AbstractScene(IoChangedListener *impl, const Parameter &parameter);
	virtual ~AbstractScene() = default;
	virtual void init() = 0;
	virtual void finalize() = 0;
	virtual void update() = 0;
	virtual void draw() const = 0;

};

