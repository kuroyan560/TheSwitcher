#include "DxLib.h"
#include "SelectScene.h"
#include "UsersInput.h"
#include"Map.h"
#include"SoundEmitter.h"
//セレクトシーンから移動できるシーンがあればここにinclude
#include "GameScene.h"
#include "WindowSize.h"

const char* SelectScene::CLEARED = "Cleared";
int SelectScene::TUTORIAL_GRAPH = 0;

StageDoorObj SelectScene::_entrance = StageDoorObj();
int SelectScene::_nowSelect = 0;
bool SelectScene::_camScrollStartFlag = true;
int SelectScene::_clearStage = 0;
int SelectScene::_bgGraph = 0;
int SelectScene::_shadowGraph = 0;
const Vector2<float> SelectScene::PLAYER_POS = { 250,500 };

SelectScene::SelectScene(IoChangedListener* impl, const Parameter& parameter, Fade* Fader, GoalEffect* GoalEffecter)
	: AbstractScene(impl, parameter, Fader, GoalEffecter),
	_playerGraph("_resource/graphics/player_wait.png", true, 5, 15, { 5,1 }, { 65,65 }),
	_playerMagicGraph("_resource/graphics/player_magic.png", true, 6, 6, { 6,1 }, { 64,64 }, 55, false) {

	if (!TUTORIAL_GRAPH) {
		TUTORIAL_GRAPH = LoadGraph("_resource/graphics/tutorial_select.png");
		_bgGraph = LoadGraph("_resource/graphics/backGround_select.png");
		_shadowGraph = LoadGraph("_resource/graphics/shadow.png");
	}

	//ステージ１情報入力
	_entrance.AddStageDoor("_resource/graphics/entrance.png");
	_stageObj.push_back(new Stage());
	_stageObj[0]->SetMapChipNum(STAGE_ONE_MAP_NUM);
	_stageObj[0]->AddMapData(*_mapLayer1_1);
	_stageObj[0]->AddMapData(*_mapLayer1_2);
	_stageObj[0]->AddMapData(*_mapLayer1_3);
	_stageObj[0]->AddMapData(*_mapLayer1_4);
	_stageObj[0]->AddMapData(*_mapLayer1_5);
	_stageObj[0]->SetPlayerSpawnPos({ 0,0 }, 0);

	//ステージ２情報入力
	_entrance.AddStageDoor("_resource/graphics/entrance.png");
	_stageObj.push_back(new Stage());
	_stageObj[1]->SetMapChipNum(STAGE_TWO_MAP_NUM);
	_stageObj[1]->AddMapData(*_mapLayer2_1);
	_stageObj[1]->AddMapData(*_mapLayer2_2);
	_stageObj[1]->AddMapData(*_mapLayer2_3);
	_stageObj[1]->SetPlayerSpawnPos({ 0,0 }, 0);

	//ステージ３情報入力
	_entrance.AddStageDoor("_resource/graphics/entrance.png");
	_stageObj.push_back(new Stage());
	_stageObj[2]->SetMapChipNum(STAGE_THREE_MAP_NUM);
	_stageObj[2]->AddMapData(*_mapLayer3_1);
	_stageObj[2]->AddMapData(*_mapLayer3_2);
	_stageObj[2]->AddMapData(*_mapLayer3_3);
	_stageObj[2]->SetPlayerSpawnPos({ 0,0 }, 0);

	//ステージ４情報入力
	_entrance.AddStageDoor("_resource/graphics/entrance.png");
	_stageObj.push_back(new Stage());
	_stageObj[3]->SetMapChipNum(STAGE_FOUR_MAP_NUM);
	_stageObj[3]->AddMapData(*_mapLayer4_1);
	_stageObj[3]->AddMapData(*_mapLayer4_2);
	_stageObj[3]->AddMapData(*_mapLayer4_3);
	_stageObj[3]->AddMapData(*_mapLayer4_4);
	_stageObj[3]->SetPlayerSpawnPos({ 2,2 }, 2);

	//ステージ５情報入力
	_entrance.AddStageDoor("_resource/graphics/entrance.png");
	_stageObj.push_back(new Stage());
	_stageObj[4]->SetMapChipNum(STAGE_FIVE_MAP_NUM);
	_stageObj[4]->AddMapData(*_mapLayer5_1);
	_stageObj[4]->AddMapData(*_mapLayer5_2);
	_stageObj[4]->AddMapData(*_mapLayer5_3);
	_stageObj[4]->SetPlayerSpawnPos({ 0,0 }, 1);

	//ステージ６情報入力
	_entrance.AddStageDoor("_resource/graphics/entrance.png");
	_stageObj.push_back(new Stage());
	_stageObj[5]->SetMapChipNum(STAGE_SIX_MAP_NUM);
	_stageObj[5]->AddMapData(*_mapLayer6_1);
	_stageObj[5]->AddMapData(*_mapLayer6_2);
	_stageObj[5]->AddMapData(*_mapLayer6_3);
	_stageObj[5]->AddMapData(*_mapLayer6_4);
	_stageObj[5]->AddMapData(*_mapLayer6_5);
	_stageObj[5]->SetPlayerSpawnPos({ 0,0 }, 1);

	clearedFlag = false;

	if (parameter.get(CLEARED) == 1) {
		_entrance.RaiseClearFlag(_nowSelect);
		clearedFlag = true;
	}
}

SelectScene::~SelectScene() {
	for (int i = 0; i < _stageObj.size(); i++) {
		delete _stageObj[i];
	}
}

void SelectScene::init(){
	leftFlag = false;
	rightFlag = false;
	if (_camScrollStartFlag) {
		camera.Init(_stageObj.size(), _nowSelect);
		_camScrollStartFlag = false;
	}
	else {
		camera.Init(_nowSelect + 1, _nowSelect);
	}
	_floor.Init(_stageObj.size());
	sceneChangeFlag = false;

	PlayBGM(SELECT);

	_turn = true;
}

void SelectScene::finalize(){
}

void SelectScene::update() {
	LoopImage::FlameUpdate();
    InputUpdate();

	_playerMagicGraph.Update();

	//カメラのアップデート
	camera.Update();

	//入り口の更新
	_entrance.Update();

	if (!sceneChangeFlag && !clearedFlag) {
		SelectUpdate();
	}

	if (sceneChangeFlag) {

		if (_playerMagicGraph.DrawComplete() == true) {
			_mFader->TurnBlack();
		}

		if (_mFader->TurnBlackTrigger() == true) {
			StopBGM(SELECT);
			Parameter parameter1;
			parameter1.set(GameScene::StageTag, _stageObj[_nowSelect]);
			Parameter parameter2;
			parameter2.set(GameScene::StageNumTag, _nowSelect);
			_implSceneChanged->onSceneChanged(Scenes::Game, parameter1, parameter2, false);
		}
	}
	else {
		if (JustInput(KEY_INPUT_SPACE) && camera.NowScroll() == false && clearedFlag == false) {
			//if (_nowSelect < _clearStage + 1) {
				_playerMagicGraph.AnimationStart();
				PlaySE(MAGIC);
				sceneChangeFlag = true;
			//}
		}
	}

	if (clearedFlag && _entrance.AnimationComplete(_nowSelect) == true) {
		clearedFlag = false;
		if (((_clearStage + 1) < _stageObj.size() && _clearStage <= _nowSelect) || _clearStage == 0) {
			_clearStage++;
		}
	}
	if (clearedFlag && _mGoalEffecter->NowGoalEffect() == false) {
		_entrance.LightAnimation(_nowSelect);
	}

    if (JustInput(KEY_INPUT_ESCAPE)) {
        DxLib_End();
        exit(0);
    }
}

void SelectScene::SelectUpdate(){
	if (camera.NowScroll() == false) {
		_turn = true;

		if ((Press(KEY_INPUT_LEFT) || leftFlag) && 0 < _nowSelect) {
			_nowSelect--;
			camera.MoveSet(_nowSelect);
			PlaySE(WALK);
			_turn = false;
			leftFlag = false;
		}
		else if ((Press(KEY_INPUT_RIGHT) || rightFlag) && _nowSelect + 1<= _stageObj.size()-1) {
			_nowSelect++;
			camera.MoveSet(_nowSelect);
			PlaySE(WALK);
			_turn = true;
			rightFlag = false;
		}
	}
	else if (camera.CanInputSelect()==true) {
		if (!leftFlag && !rightFlag) {
			if (JustInput(KEY_INPUT_LEFT) && 0 < _nowSelect) {
				leftFlag = true;
			}
			else if (JustInput(KEY_INPUT_RIGHT) && _nowSelect < _stageObj.size() - 1) {
				rightFlag = true;
			}
		}
	}
}

void SelectScene::draw() {
	DrawGraph(0, 0, _bgGraph, true);
	_entrance.Draw(camera.GetScrollX());
	_floor.Draw(camera.GetScrollX());
	//影の描画
	SetDrawBlendMode(DX_BLENDMODE_MULA, 130);
	DrawExtendGraph(PLAYER_POS.x - PLAYER_SIZE / 2, PLAYER_POS.y + PLAYER_SIZE / 2 - 40,
					PLAYER_POS.x + PLAYER_SIZE / 2,PLAYER_POS.y + PLAYER_SIZE / 2 + 24, _shadowGraph, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//プレイヤーの描画
	if (_playerMagicGraph.NowAnimation() == false) {
		_playerGraph.Draw(PLAYER_POS, { PLAYER_SIZE,PLAYER_SIZE }, _turn);
	}
	_playerMagicGraph.Draw(PLAYER_POS, { PLAYER_SIZE,PLAYER_SIZE }, _turn);
	DrawGraph(GetWinSize().x - 605, GetWinSize().y - 62, TUTORIAL_GRAPH, true);
}
