#include "GameScene.h"
#include"SelectScene.h"
#include "DxLib.h"
#include "UsersInput.h"
#include "WindowSize.h"
#include"Graphics.h"
#include"SoundEmitter.h"

const char *GameScene::StageTag = "StageTag";      //ステージ決定用のパラメータ
const char* GameScene::StageNumTag = "StageNumTag";
int GameScene::_bgGraph = 0;
int GameScene::_tutorialGraph = 0;

GameScene::GameScene(IoChangedListener *impl, const Parameter &parameter,Fade* Fader, GoalEffect* GoalEffecter)
    : AbstractScene(impl, parameter,Fader, GoalEffecter){

	_selectedStage = parameter.stageGet(StageTag);
	if (!_tutorialGraph) {
		_tutorialGraph = LoadGraph("_resource/graphics/tutorial.png");
		_bgGraph = LoadGraph("_resource/graphics/backGround_UI.png");

	}
}

GameScene::GameScene(IoChangedListener* impl, const Parameter& parameter1, const Parameter& parameter2, Fade* Fader, GoalEffect* GoalEffecter)
	:AbstractScene(impl, parameter1,parameter2, Fader, GoalEffecter)
{
	_selectedStage = parameter1.stageGet(StageTag);
	_thisStageNum = parameter2.get(StageNumTag);
	if (!_tutorialGraph) {
		_tutorialGraph = LoadGraph("_resource/graphics/tutorial.png");
		_bgGraph = LoadGraph("_resource/graphics/backGround_UI.png");
	}
}

GameScene::~GameScene() {
}

void GameScene::init() {
	_selectedStage->Init(_mFader,this);
	_player.Init(_selectedStage, _selectedStage->GetMapChipSize());
	_stock.Init(_selectedStage->GetMapChipSize());
	_mFader->Initialize();
	_mGoalEffecter->Initialize();
	_returnSelectScene = false;
	_stageResetFlag = false;
	_spaceFlame = 0;

	PlayBGM(GAME);
}

void GameScene::finalize() {
}

void GameScene::update() {

	LoopImage::FlameUpdate();
	InputUpdate();

	_selectedStage->Update(_player.GetWhatOnPlayer());
	_player.Update(CanMove());
	_stock.Update(_player.GetWhatOnPlayer());

	//中断
	Interrupt();

	//ゴール演出
	Goal();

	//長押ししたときステージ全体リセット
	StageReset();
}

void GameScene::draw() {
	DrawGraph(720, 0, _bgGraph, false);
	_selectedStage->Draw(_player.GetWhatOnPlayer());
	if (_player.GetWhatOnPlayer() == PASTE_LAYER) {
		_stock.Draw(_selectedStage->GetNowMap());
	}
	DrawGraph(GetWinSize().x - 282, GetWinSize().y - 70, _tutorialGraph, true);
	_player.Draw((30 < _spaceFlame) ? true : false);
}

bool GameScene::CanMove(){

	if (_mFader->NowFadeFlag() == true || _mGoalEffecter->NowGoalEffect() == true) {
		return false;
	}
	else return true;
}

void GameScene::Interrupt(){
	//中断、フェード開始
	if (JustInput(KEY_INPUT_ESCAPE) == true && _selectedStage->GetGoalFlag() == false) {
		_returnSelectScene = true;
		_mFader->TurnBlack();
	}
	//中断後、フェード演出とシーン遷移（ステージ選択画面へ）
	if (_returnSelectScene && _mFader->TurnBlackTrigger() == true) {
		StopBGM(GAME);
		Parameter parameter;
		_implSceneChanged->onSceneChanged(Scenes::Select, parameter,false);
		//_implSceneChanged->sceneStackPop();
	}
}

void GameScene::Goal(){
	//ゴール演出
	if (_selectedStage->GetGoalFlag() == true) {
		_mGoalEffecter->ReachToGoal(_player.CenterPos(), { 870,150+86 });
	}
	//ゴール演出後、ステージ選択画面に戻る
	if (_mGoalEffecter->FontDisappearTrigger() == true) {
		StopBGM(GAME);
		
		parameter;
		parameter.set(SelectScene::CLEARED, 1);
		_implSceneChanged->onSceneChanged(Scenes::Select, parameter,false);
		//_implSceneChanged->sceneStackPop();
	}
}

void GameScene::StageReset(){
	if (JustInput(KEY_INPUT_SPACE) == true) {
		_spaceFlame = 1;
	}
	else if (Input(KEY_INPUT_SPACE) == true) {
		if (_spaceFlame) {
			_spaceFlame++;
		}
	}
	else {
		_spaceFlame = 0;
	}

	if (120 < _spaceFlame) {
		_mFader->TurnBlack();
		_stageResetFlag = true;
	}

	if (_mFader->TurnBlackTrigger() == true && _stageResetFlag) {
		this->init();
	}
}

void GameScene::CopyStock(LayerMapData& OriginalMap){
	_stock.Copy(OriginalMap);

}

void GameScene::PasteMap(LayerMapData& ToCopyMap){
	_stock.Paste(ToCopyMap);
}

void GameScene::StockMiniMapDraw()
{
	_stock.MiniMapDraw();
}

Vector2<int> GameScene::PlayerPlace()
{
	int X = _player.CenterPos().x / _selectedStage->GetMapChipSize();
	int Y = _player.CenterPos().y / _selectedStage->GetMapChipSize();
	return Vector2<int>{X, Y};
}
