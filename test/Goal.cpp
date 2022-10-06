#include "Goal.h"
#include"DxLib.h"
#include"WindowSize.h"

const Vector2<int> Goal::SIZE = { 64,64 };
const char* Goal::GRAPH_PASS = "";
int Goal::GRAPH = 0;

Goal::Goal()
{
	/*if (GRAPH == 0)
	{
		GRAPH = LoadGraph("GRAPH_PASS");
	}*/
}

Goal::~Goal()
{
}

void Goal::Initialize(int WallHeight)
{
	pos = { (float)(GetWinSize().x / 2 - SIZE.x),(float)(WallHeight - SIZE.y) };
}

void Goal::Draw(Vector2<float> CamPos)
{
	if (GRAPH != 0){
		DrawGraph(pos.x - CamPos.x, pos.y - CamPos.y, GRAPH, true);
	}
	else{
		DrawBox(pos.x - CamPos.x, pos.y - CamPos.y, pos.x + SIZE.x - CamPos.x, pos.y + SIZE.y - CamPos.y, GetColor(255, 0, 0), true);
	}
}
