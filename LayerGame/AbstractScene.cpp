#include "AbstractScene.h"

AbstractScene::AbstractScene(IoChangedListener *impl, const Parameter &parameter1, Fade* Fader,GoalEffect* GoalEffecter) :
	_implSceneChanged(impl),_mFader(Fader),_mGoalEffecter(GoalEffecter) {

}

AbstractScene::AbstractScene(IoChangedListener* impl, const Parameter& parameter1, const Parameter& parameter2, Fade* Fader, GoalEffect* GoalEffecter):
	_implSceneChanged(impl), _mFader(Fader), _mGoalEffecter(GoalEffecter)
{
}
