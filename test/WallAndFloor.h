#pragma once
#include"Vector2.h"
class WallAndFloor
{

public:
	static const int WALL_WIDTH = 300;
	static const int SPEAR_WIDTH = 50;
	static const int FLOOR_HEIGHT = 100;

private:
	static const char* WALL_GRAPH_PASS;
	static const char* FLOOR_GRAPH_PASS;

	int _wallGraph;
	int _floorGraph;

	Vector2<float>_wallSize;
	Vector2<float>_floorSize;

	Vector2<float>_initWallPos[2][2];
	Vector2<float>_initFloorPos;

	Vector2<float>_wallPos[2][2];
	Vector2<float>_floorPos;

public:
	WallAndFloor();
	~WallAndFloor() {};

	void Initialize();
	void Update(const float &CamPosY);
	void Draw(Vector2<float>CamScroll) const;

	Vector2<float>* GetPtrWallPos() { return &_wallPos[0][0]; }
	Vector2<float> GetWallSize()const { return _wallSize; }
	Vector2<float> GetFloorPos()const { return _floorPos; }
	Vector2<float> GetFloorSize()const { return _floorSize; }
};