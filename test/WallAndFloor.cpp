#include "WallAndFloor.h"
#include"DxLib.h"
#include "WindowSize.h"

const char* WallAndFloor::WALL_GRAPH_PASS = "wall.png";
const char* WallAndFloor::FLOOR_GRAPH_PASS = "floor.png";

WallAndFloor::WallAndFloor()
{
	_wallSize = { WALL_WIDTH,GetWinSize().y * 2 };
	_floorSize = { GetWinSize().x,FLOOR_HEIGHT };

	_initWallPos[0][0] = { -SPEAR_WIDTH,0 };
	_initWallPos[0][1] = { GetWinSize().x - WALL_WIDTH + SPEAR_WIDTH,0 };
	_initWallPos[1][0] = { -SPEAR_WIDTH,-(GetWinSize().y * 2) };
	_initWallPos[1][1] = { GetWinSize().x - WALL_WIDTH + SPEAR_WIDTH,-(GetWinSize().y * 2) };
	_initFloorPos = { 0,GetWinSize().y - FLOOR_HEIGHT };

	_wallGraph = LoadGraph(WALL_GRAPH_PASS);
	_floorGraph = LoadGraph(FLOOR_GRAPH_PASS);
}

void WallAndFloor::Initialize()
{
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++) {
			_wallPos[i][j] = _initWallPos[i][j];
		}
	}
	_floorPos = _initFloorPos;
}

void WallAndFloor::Update(const float& CamPosY)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (_wallSize.y/2 < _wallPos[i][j].y - CamPosY) {
				_wallPos[i][j].y -= (_wallSize.y*2+1);
			}
		}
	}
}

void WallAndFloor::Draw(Vector2<float>CamScroll) const
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			DrawGraph(_wallPos[i][j].x-CamScroll.x, _wallPos[i][j].y - CamScroll.y, _wallGraph, true);
		}
	}
	DrawGraph(_floorPos.x - CamScroll.x, _floorPos.y - CamScroll.y, _floorGraph, true);
}
