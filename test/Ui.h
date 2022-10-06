#pragma once
#include"Vector2.h"
#include"DxLib.h"

class Ui {
public:

	Ui();

	void Initialize();
	void Finalize();

	void Update(Vector2<float> PlPos);
	void Draw()const;

private:
	
	static const Vector2<float> _UI_POS;
	static const Vector2<float> _UI_SIZE;
	static const float _GOAL_POS;

	Vector2<float> _plPos, _nowPos;
	int _uiGraph;
	int _plGraph;
};

