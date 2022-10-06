#pragma once
#include<vector>
#include"MapData.h"
#include"Vector2.h"
#include"StageInfoTransInterFace.h"
#include"Graphics.h"
#include"Emitter.h"
#include"Fade.h"
#include"GameMgrTranser.h"

class Stage : public StageInfoTransInterFace {

private:
	static int NUM_GRAPH[6];
	static int ARROW_GRAPH;
	static LoopImage MOVE_UP_GRAPH;
	static LoopImage MOVE_DOWN_GRAPH;
	static int MAGIC_CIRCLE_GRAPH;
	static int PLAYER_LAYER_BOX_GRAPH;

	std::vector<LayerMapData> _mapData;

	//レイヤーマップUIの描画座標
	float _layerY;

	//何×何のマップ縮尺か
	int _mapSizeChipNum;
	float _chipSize;

	//プレイヤーの初期化位置
	Vector2<float> _playerSpawnPos;
	int _playerSpawnLayer;

	//プレイヤーがいるレイヤー
	int _playerLayer;

	//プレイヤーがいるマップを囲う赤い四角の左上座標
	Vector2<float>_playerMapBoxPos;
	Vector2<float>_playerMapTo;

	//効果の表示位置
	Vector2<float> _markPos;

	//クリアーフラグ
	bool _clearFlag;

	//ミニマップ魔法陣
	bool _magicCircleDrawFlag;
	float _magicCircleAngle;

	//コピー時の爆発エミッター
	static const int EXPLOSION_EMITTER_NUM = 10;
	ExplosionEmitter _expEmitter[EXPLOSION_EMITTER_NUM];

	//フェードオブジェクトのポインタ
	Fade* _fadePtr;

	//ゲームシーンとの窓口
	GameMgrTranser* _mGameScene;

	//移動中か
	bool _floorUpFlag;
	bool _floorDownFlag;

	bool _resetFlag;

public:
	Stage();
	~Stage() {};

	//設定用関数
	void SetMapChipNum(int Num);
	void AddMapData(char *MapArray);
	void SetPlayerSpawnPos(Vector2<float> Pos,int Layer);

	//初期化用関数
	void Init(Fade* FadeObj,GameMgrTranser* GameScene);
	void PlayerMapBoxPosInit();

	//情報受け渡し関数
	float GetMapChipSize() { return _chipSize; }

	//情報受け渡し関数（継承）
	virtual Vector2<float> GetPlayerSpawnPos()const override{ return _playerSpawnPos; }
	virtual int GetMapData(Vector2<float> CenterPos)override;
	virtual int PressSwitch(int WhatSwitch)override;
	virtual void ReachGoal()override;

	void Update(const int WhatOnPlayer);
	void ExplosionEmit(const int WhatOnPlayer);
	void Draw(const int WhatOnPlayer);
	void MiniMapDraw(const int WhatOnPlayer);
	void PlayerMapBoxDraw();

	bool GetGoalFlag()const { return _clearFlag; }

	LayerMapData& GetNowMap();
};