#pragma once
#include"DxLib.h"
#include"Vector2.h"
#include"easing.h"

class Item {
public:

	Item();

	void Initialize(int x, int y, int WPB, int HPB);
	void Finalize();

	void Update();
	void Draw(Vector2<float> CamPos) const;

	const Vector2<float> GetPos();
	void SetItemGet();

private:

	float _t;
	int _animationFlame;

	Vector2<float> _itemPos, _iniItemPos;
	bool _isAliveFlag;

	int _timer;
	bool _disappearFlag;

	static int _graph[5];
	static int _animationMaxFlame;
	static int _animationSpeed;
	static int _animationTimer;

	static int _disappearTime;
};
