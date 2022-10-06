#include "Item.h"
//#include"WallAndFloor.h"
//#include"WindowSize.h"
int Item::_graph[] = { 0 };

int Item::_animationMaxFlame = 4;
int Item::_animationSpeed = 60;
int Item::_animationTimer = 0;

int Item::_disappearTime = 5;

Item::Item() {

	_itemPos = { 0,0 };

	_disappearFlag = true;
	_isAliveFlag = false;

	_t = 0;
	_timer = 0;

	_animationFlame = 0;
	_iniItemPos = { 0 ,0 };

	if (!_graph[0]) { LoadDivGraph("AnimationCheck.png", 4, 4, 1, 32, 32, _graph, TRUE); }

}

void Item::Initialize(int x, int y, int WPB, int HPB) {

	//_itemPos = { (float)(x * WPB + WallAndFloor::WALL_WIDTH),(float)(-y * HPB + GetWinSize().y - WallAndFloor::FLOOR_HEIGHT) };
	_iniItemPos = _itemPos;

	_t = 0;

	_disappearFlag = false;
	_timer = 0;

	_isAliveFlag = false;
}

void Item::Finalize() {
	_isAliveFlag = false;
	_disappearFlag = true;
}

void Item::Update() {

	if (_isAliveFlag) {

		if (1.0F >= _t) { _t += 0.02F; }
		if (_t >= 1.0F) {

			_t = 1.0F;
			_timer++;

		}

		_itemPos.x = _iniItemPos.x;
		_itemPos.y = _iniItemPos.y + -(Ease(Out, Back, _t) * 100);


		if (_timer > _disappearTime) { 
			
			_disappearFlag = true; 
		
		}

	}


	_animationTimer++;

	if (_animationTimer > _animationSpeed && _animationFlame < _animationMaxFlame) {

		_animationFlame++;
		_animationTimer = 0;

	}
	if (_animationFlame >= _animationMaxFlame) {

		_animationFlame = 0;

	}

}

void Item::Draw(Vector2<float> CamPos) const{

	if (!_disappearFlag) {

		if (!_graph[0] || _graph[0] == -1) {

			DrawBox(_itemPos.x - CamPos.x, _itemPos.y - CamPos.y, _itemPos.x + 50 - CamPos.x, _itemPos.y + 50 - CamPos.y, GetColor(255, 255, 255), TRUE);

		}
		else {

			DrawGraph(_itemPos.x - CamPos.x, _itemPos.y - CamPos.y, _graph[_animationFlame], TRUE);

		}
	}
}

const Vector2<float> Item::GetPos() {

	return _itemPos;
}

void Item::SetItemGet() {

	_isAliveFlag = true;

}