#pragma once
#include"Vector2.h"

class Goal
{
	static const Vector2<int> SIZE;
	static const char* GRAPH_PASS;
	static int GRAPH;
	Vector2<float> pos;

public:
	Goal();
	~Goal();

	void Initialize(int WallHeight);
	void Draw(Vector2<float> CamPos);
};

