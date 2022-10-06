#include "GameScene.h"
#include "DxLib.h"
#include "UsersInput.h"
#include "Player.h"
#include "WindowSize.h"

const char *GameScene::StageTag = "StageTag";      //ステージ決定用のパラメータ

GameScene::GameScene(IoChangedListener *impl, const Parameter &parameter)
    : AbstractScene(impl, parameter),
	camera(GetWinSize()),
    _player(Player::Direction::DIRECTION_LEFT) {
    _selectTag = parameter.get(StageTag);
    _counter = 0;
    stageObj = new Stage*[3];
    stageObj[0] = new Stage1(120,2000);
    stageObj[1] = new Stage2(120,GetWinSize().y*7);
    stageObj[2] = new Stage3(120,2000);
}

GameScene::~GameScene() {
	for (int i = 0; i < 3; i++) {
        delete stageObj[i];
	}
    delete[] stageObj;
}

void GameScene::init() {
    _counter = 0;
    stageObj[_selectTag]->Init(&enemy[0], &item[0], goal);
    camera.Initialize();
    score.Initialize();
    waf.Initialize();
    _player.Initialize(GetWinSize(),waf.GetFloorSize().y,GetWinSize().x-250,
        stageObj[_selectTag]->GetFPB(),stageObj[_selectTag]->GetHPB());
}

void GameScene::finalize() {
	for(int i = 0; i < 5;i++) {
        enemy[i].Finalize();
        item[i].Finalize();
	}
}

void GameScene::update() {
	_counter++;
	InputUpdate();
    waf.Update(camera.GetCamPos().y);
    _player.Update(stageObj[_selectTag]->GetFPB(),_counter);
    ui.Update(_player.GetPos());
    for (int i = 0; i < 5; i++) {
        enemy[i].Update();
        item[i].Update();
    }
	WallAndFloorCheck();
    camera.Update(_player.GetPos().y);
	score.Update(_counter);
	playBPM();
}

void GameScene::draw() const {
    waf.Draw(camera.GetCamPos());
    for (int i = 0; i < 5; i++) {
        enemy[i].Draw(camera.GetCamPos());
        item[i].Draw(camera.GetCamPos());
    }
    _player.Draw(camera.GetCamPos());
	
    score.Draw();
    ui.Draw();
}

void GameScene::WallAndFloorCheck()
{
	bool a = false;
	for (int i = 0; i < 4; i++) {
		if (HitCheck(_player.GetPos(), _player.GetSize(),
					 *(waf.GetPtrWallPos() + i), waf.GetWallSize() + Vector2<float>{_player.GetCanJumpSizeX(), 0})) {
			if (JustOut(KEY_INPUT_SPACE) == true) {
				_player.Jump(stageObj[_selectTag]->GetFPB(), _counter,camera);
				a = true;
				break;
			}
		}
	}
	if (!a) {
		for (int i = 0; i < 4; i++) {
			if (HitCheck(_player.GetPos(), _player.GetSize(),
						 *(waf.GetPtrWallPos() + i), waf.GetWallSize())) {
				if (_player.TriggerTouchWall() == true) {
					camera.CamShake();

					/*for (int j = 0; j < EMITTER_NUM; j++) {
						if (emit[j].GetAlive() == false) {
							emit[j].EmitKickSmoke(player.GetPos() + player.GetSize() - camera.GetCamPos());
							break;
						}
					}*/
				}

				_player.SmallJump(stageObj[_selectTag]->GetFPB(), _counter);

				if ((i + 1) % 2 != 0) {
					//左壁
					_player.StickWall(0, WallAndFloor::SPEAR_WIDTH, waf.GetWallSize().x, GetWinSize().x);
					break;
				}
				else {
					//右壁
					_player.StickWall(1, WallAndFloor::SPEAR_WIDTH, waf.GetWallSize().x, GetWinSize().x);
					break;
				}
			}
		}
	}

	//床
	if (HitCheck(_player.GetPos(), _player.GetSize(), waf.GetFloorPos(), waf.GetFloorSize()))
	{
		_player.GroundFloor(waf.GetFloorSize().y, GetWinSize().y, stageObj[_selectTag]->GetFPB(), _counter);
	}
}

void GameScene::playBPM() {
	if (_counter % stageObj[_selectTag]->GetFPB() == 0) {
		PlaySoundMem(lowTap, DX_PLAYTYPE_BACK);
	}
}

bool GameScene::HitCheck(Vector2<float> playerPos, Vector2<float> playerSize, Vector2<float> objPos, Vector2<float> objSize)
{
	Vector2<float> PlRightDown = { playerPos.x + playerSize.x,playerPos.y + playerSize.y },
		objRightDown = { objPos.x + objSize.x,objPos.y + objSize.y };


	if (objPos.x <= PlRightDown.x &&
		playerPos.x <= objRightDown.x &&
		objPos.y <= PlRightDown.y &&
		playerPos.y <= objRightDown.y) {

		return true;

	}
	else {

		return false;

	}
}