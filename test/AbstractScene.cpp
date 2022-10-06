#include "AbstractScene.h"

AbstractScene::AbstractScene(IoChangedListener *impl, const Parameter &parameter) :
	_implSceneChanged(impl) {

}
