#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include"Player.h"
#include"Stage.h"
#include"GameMgrTranser.h"

class GameScene : public AbstractScene,GameMgrTranser
{
public:
	const static char *StageTag;
	const static char *StageNumTag;


	GameScene(IoChangedListener *impl, const Parameter &parameter,Fade* Fader,GoalEffect* GoalEffecter);
	GameScene(IoChangedListener* impl, const Parameter& parameter1, const Parameter& parameter2, Fade* Fader, GoalEffect* GoalEffecter);
	~GameScene();
	void init() override;
	void finalize() override;
	void update() override;
	void draw() override;

	bool CanMove();
	void Interrupt();
	void Goal();
	void StageReset();

	//ステージオブジェクトから要求された処理をする関数
	virtual void CopyStock(LayerMapData& OriginalMap)override;
	virtual void PasteMap(LayerMapData& ToCopyMap)override;
	virtual void StockMiniMapDraw()override;
	virtual bool GetEmpty()override { return _stock.GetEmpty(); }
	virtual Vector2<int> PlayerPlace()override;

private:
	static int _bgGraph;
	static int _tutorialGraph;
	bool _stageResetFlag;
	int _spaceFlame;
	bool _returnSelectScene;
	Stage* _selectedStage;
	int _thisStageNum;
	Player _player;

	StockMapData _stock;
};