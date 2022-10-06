#pragma once
#include"Vector2.h"

static enum ChipType {
	NONE, WALL, GOAL, 
	GO_UPPER_LAYER, GO_LOWER_LAYER,
	COPY_LAYER,PASTE_LAYER,
	RESET_LAYER,
	ZONE
};

//ステージの情報を受け取るインターフェース
class StageInfoTransInterFace {
public:
	virtual ~StageInfoTransInterFace() {};
	//初期化用関数
	virtual Vector2<float> GetPlayerSpawnPos()const = 0;	//プレイヤー初期化位置を渡す

	//情報受け渡し関数（ステージからプレイヤーへ）
	virtual int GetMapData(Vector2<float> CenterPos) = 0;	//マップデータ取得

	//処理を要求する関数（プレイヤーからステージへ）
	virtual int PressSwitch(int WhatSwitch) = 0;

	//ゴールする
	virtual void ReachGoal() = 0;
};