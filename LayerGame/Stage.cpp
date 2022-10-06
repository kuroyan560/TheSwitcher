#include "Stage.h"
#include"DxLib.h"
#include"WindowSize.h"
#include"UsersInput.h"
#include"SoundEmitter.h"
#include"WindowSize.h"

int Stage::NUM_GRAPH[6] = { 0 };
int Stage::ARROW_GRAPH = 0;
LoopImage Stage::MOVE_UP_GRAPH = LoopImage();
LoopImage Stage::MOVE_DOWN_GRAPH = LoopImage();
int Stage::MAGIC_CIRCLE_GRAPH = 0;
int Stage::PLAYER_LAYER_BOX_GRAPH = 0;

static float lerp(float start, float end, float t)
{
	return (1 - t) * start + t * end;
}

static float value(float a)
{
	if (a < 0)return -a;
	else return a;
}

static float PI = 3.14159265359;

Stage::Stage(){
	if (ARROW_GRAPH == 0) {
		LoadDivGraph("_resource/graphics/number.png", 6, 6, 1, 190, 190, NUM_GRAPH);
		ARROW_GRAPH = LoadGraph("_resource/graphics/arrow.png");
		MOVE_UP_GRAPH.Init("_resource/graphics/moveUp.png", true, 3, 6, { 3,1 }, { 64,64 });
		MOVE_DOWN_GRAPH.Init("_resource/graphics/moveDown.png", true, 3, 6, { 3,1 }, { 64,64 });
		MAGIC_CIRCLE_GRAPH = LoadGraph("_resource/graphics/magicCircle.png");
		PLAYER_LAYER_BOX_GRAPH = LoadGraph("_resource/graphics/playerLayerBox.png");
	}
}

void Stage::SetMapChipNum(int Num){
	_mapSizeChipNum = Num;
	_chipSize = GetWinSize().y / Num;
}

void Stage::AddMapData(char* MapArray){
	_mapData.push_back(LayerMapData(MapArray, _mapSizeChipNum));
}

void Stage::SetPlayerSpawnPos(Vector2<float> Pos, int Layer){
	_playerSpawnPos = Pos;
	_playerSpawnLayer = Layer;
}

void Stage::Init(Fade* FadeObj, GameMgrTranser* GameScene){
	_clearFlag = false;
	_playerLayer = _playerSpawnLayer;
	PlayerMapBoxPosInit();

	_layerY = 0.0F;
	_magicCircleAngle = 0.0F;
	_magicCircleDrawFlag = true;

	for (int i = 0; i < EXPLOSION_EMITTER_NUM; i++) {
		_expEmitter[i].Init();
	}
	_fadePtr = FadeObj;
	_mGameScene = GameScene;
}

void Stage::PlayerMapBoxPosInit()
{
	for (int i = 0; i < _mapData.size(); i++) {
		_mapData.at(i).Init();
	}

	if (_playerLayer < 3) {
		_playerMapBoxPos.x = 1000 - 190.3 - 1.5 + (288.5 - (288.5 - 190.3) + 30) * 0;
	}
	else {
		_playerMapBoxPos.x = 1000 - 190.3 - 1.5 + (288.5 - (288.5 - 190.3) + 30) * 1;
	}
	for (int i = 0; i < 3; i++) {
		if (_playerLayer == (0 + i) || _playerLayer == (3 + i)) {
			_playerMapBoxPos.y = (32 * 2 + (190.3 + 3) * i);
			break;
		}
	}
	_playerMapTo = _playerMapBoxPos;
}

int Stage::GetMapData(Vector2<float> CenterPos){
	int x = CenterPos.x / _chipSize;
	int y = CenterPos.y / _chipSize;

	return _mapData.at(_playerLayer).GetChipType(x, y);
}

int Stage::PressSwitch(int WhatSwitch){
	if (WhatSwitch == NONE) {
		//何もしない
		return -1;
	}
	else if (WhatSwitch == GO_UPPER_LAYER && 0 < _playerLayer &&
			 _mapData[_playerLayer - 1].GetChipType(_mGameScene->PlayerPlace().x, _mGameScene->PlayerPlace().y) != WALL) {
		_floorUpFlag = true;
		_fadePtr->GoingUpFloor();
		PlaySE(FLOOR);
		return 0;
	}
	else if (WhatSwitch == GO_LOWER_LAYER && _playerLayer < _mapData.size() - 1 &&
			 _mapData[_playerLayer + 1].GetChipType(_mGameScene->PlayerPlace().x, _mGameScene->PlayerPlace().y) != WALL) {
		_floorDownFlag = true;
		_fadePtr->GoingDownFloor();
		PlaySE(FLOOR);
		return 0;
	}
	else if (WhatSwitch == COPY_LAYER) {
		_mGameScene->CopyStock(_mapData[_playerLayer]);
		PlaySE(MAGIC);
		return 1;
	}
	else if (WhatSwitch == PASTE_LAYER && _mGameScene->GetEmpty() == false) {
		_mGameScene->PasteMap(_mapData[_playerLayer]);
		PlaySE(MAGIC);
		return 1;
	}
	else if (WhatSwitch == RESET_LAYER) {
		_resetFlag = true;
		_fadePtr->TurnBlack();
		PlaySE(RESET);
		return 0;
	}
	else {

		return 0;
	}
}

void Stage::ReachGoal(){
	if (!_clearFlag) {
		_clearFlag = true;
		PlaySE(GOALED);
		SetFadeOut(GAME, 3);
	}
}

void Stage::Update(const int WhatOnPlayer){

	_mapData[_playerLayer].Update();

	int i = 0;
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 3; y++) {

			if (i == _mapData.size()) {
				break;
			}
			float posX = 1000 - 190.3 - 1.5 + (288.5 - (288.5 - 190.3) + 30) * x;
			float posY = (32 * 2 + (190.3 + 15) * y);

			if (i++ == _playerLayer) {

				//プレイヤーがいるマップを赤い四角の移動目標先
				_playerMapTo = { posX,posY };

				//プレイヤーが乗っているマスの効果の図示座標
				_markPos = { (float)(posX + 190.3 / 2),posY };
			}
		}
	}



	//魔法陣回転
	_magicCircleAngle++;
	if (_magicCircleAngle == 360) {
		_magicCircleAngle = 0.0F;
	}

	//コピーによる土煙
	ExplosionEmit(WhatOnPlayer);

	//コピー時爆発エミッター更新
	for (int i = 0; i < EXPLOSION_EMITTER_NUM; i++) {
		_expEmitter[i].Update();
	}

	//階層移動
	if (_fadePtr->ChangeFloorTrigger() == true) {
		if (_floorUpFlag) {
			_playerLayer--;
			_mapData[_playerLayer].CopyCountUp();
			_floorUpFlag = false;
		}
		else if (_floorDownFlag) {
			_playerLayer++;
			_mapData[_playerLayer].CopyCountUp();
			_floorDownFlag = false;
		}
	}
	//リセットマス
	if (_fadePtr->TurnBlackTrigger() == true && _resetFlag) {
		_mapData.at(_playerLayer).Init();
		_resetFlag = false;
	}
}

void Stage::ExplosionEmit(const int WhatOnPlayer){
	if (JustOut(KEY_INPUT_SPACE) == true) {
		if (WhatOnPlayer == COPY_LAYER) {
			for (int i = 0; i < EXPLOSION_EMITTER_NUM; i++) {
				if (_expEmitter[i].GetAliveFlag() == false) {
					_expEmitter[i].Emit({ 903 + 190 * 7 / 6,450 + 190 / 2 });
					break;
				}
			}
		}
		else if (WhatOnPlayer == PASTE_LAYER && _mGameScene->GetEmpty() == false) {
			for (int i = 0; i < EXPLOSION_EMITTER_NUM; i++) {
				if (_expEmitter[i].GetAliveFlag() == false) {
					_expEmitter[i].Emit({ GetWinSize().y / 2,GetWinSize().y / 2 });
					break;
				}
			}
		}
	}
}

void Stage::Draw(const int WhatOnPlayer){

	_mapData.at(_playerLayer).Draw();
	//ミニマップ
	MiniMapDraw(WhatOnPlayer);
}

void Stage::MiniMapDraw(const int WhatOnPlayer){
	int i = 0;
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 3; y++) {

			//全部マップ分表示終わったら終了
			if (i == _mapData.size()) {
				break;
			}

			float posX = 1000 - 190.3 - 1.5 + (288.5 - (288.5 - 190.3) + 30) * x;
			float posY = (32 * 2 + (190.3 + 15) * y);

			//ミニマップ描画
			_mapData.at(i++).MiniMapDraw(190.3 / _mapSizeChipNum, { posX, posY });

			//マップが４つ以上なら矢印描画
			if (3 < _mapData.size()) {
				//左下矢印
				if (x == 0 && y == 2) {
					DrawGraph(posX + 190.3 / 2 - 64 / 2, posY + 190.3 - 2, ARROW_GRAPH, true);
				}
				//右上矢印
				if (x == 1 && y == 0) {
					DrawGraph(posX + 190.3 / 2 - 64 / 2, posY - 64, ARROW_GRAPH, true);
				}
			}
		}
	}

	//ストックのミニマップ描画
	_mGameScene->StockMiniMapDraw();

	//プレイヤーがいるマップを囲う赤い四角
	PlayerMapBoxDraw();

	//プレイヤーが乗っているマスの効果を図示
	if (WhatOnPlayer == GO_UPPER_LAYER && 0 < _playerLayer) {
		if (_playerLayer == 3) {
			_markPos.x -= (190 + 30);
			_markPos.y += 190 * 3 + 32;
		}
		MOVE_UP_GRAPH.Draw(_markPos, { 64,64 });
	}
	else if (WhatOnPlayer == GO_LOWER_LAYER && _playerLayer < _mapData.size() - 1) {
		if (_playerLayer == 2) {
			_markPos.x += (190 + 30);
			_markPos.y -= 190 * 3 + 32;
		}
		MOVE_DOWN_GRAPH.Draw({ _markPos.x,_markPos.y + 190 }, { 64,64 });
	}

	//魔法陣描画
	if (_magicCircleDrawFlag) {
		if (WhatOnPlayer == COPY_LAYER) {
				DrawRotaGraph(_markPos.x, _markPos.y + 190 / 2, 1.0, PI / 180 * _magicCircleAngle, MAGIC_CIRCLE_GRAPH, true);
		}
		else if (WhatOnPlayer == PASTE_LAYER) {
			DrawRotaGraph(_markPos.x, _markPos.y + 190 / 2, 1.0, PI / 180 * _magicCircleAngle, MAGIC_CIRCLE_GRAPH, true);
		}
	}
	if (WhatOnPlayer != COPY_LAYER && WhatOnPlayer != PASTE_LAYER) {
		_magicCircleDrawFlag = true;
	}

	//コピー時爆発パーティクル描画
	for (int i = 0; i < EXPLOSION_EMITTER_NUM; i++) {
		_expEmitter[i].Draw();
	}
}

void Stage::PlayerMapBoxDraw()
{
	_playerMapBoxPos.x = lerp(_playerMapBoxPos.x, _playerMapTo.x, 0.3F);
	_playerMapBoxPos.y = lerp(_playerMapBoxPos.y, _playerMapTo.y, 0.3F);

	if (value(_playerMapBoxPos.x - _playerMapTo.x) < 0.1) {
		_playerMapBoxPos.x = _playerMapTo.x;
	}
	if (value(_playerMapBoxPos.y - _playerMapTo.y) < 0.1) {
		_playerMapBoxPos.y = _playerMapTo.y;
	}

	DrawGraph(_playerMapBoxPos.x, _playerMapBoxPos.y, PLAYER_LAYER_BOX_GRAPH, true);
}

LayerMapData& Stage::GetNowMap()
{
	return _mapData[_playerLayer];
}
