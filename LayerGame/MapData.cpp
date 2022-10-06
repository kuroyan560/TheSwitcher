#include "MapData.h"
#include"StageInfoTransInterFace.h"
#include"DxLib.h"
#include"WindowSize.h"

const char* MapData::GRAPH_PASS = "_resource/graphics/mapchip.png";

int MapData::GRAPH[CHIP_TYPE_NUM] = { 0 };
int MapData::COPY_STOCK_GRAPH = 0;

void MapData::Load(){
	if (GRAPH[0] == 0) {
		LoadDivGraph(GRAPH_PASS, CHIP_TYPE_NUM, CHIP_TYPE_NUM, 1, MAP_CHIP_GRAPH_SIZE, MAP_CHIP_GRAPH_SIZE, GRAPH);
		COPY_STOCK_GRAPH = LoadGraph("_resource/graphics/copyStock.png");
	}
}

void MapData::MiniMapDraw(float Size, Vector2<float> LeftUpPos){
	for (int y = 0; y < _chipNum; y++) {
		for (int x = 0; x < _chipNum; x++) {
			DrawExtendGraph(LeftUpPos.x + x * Size, LeftUpPos.y + y * Size, LeftUpPos.x + (x + 1) * Size, LeftUpPos.y + (y + 1) * Size, GRAPH[GetChipType(x, y)], true);
		}
	}
}

int MapData::GetChipType(int x, int y) const{
	if (0 <= x && x < _chipNum && 0 <= y && y < _chipNum) {
		return _mapData[y][x];
	}
	else {
		return WALL;
	}
}

//通常マップデータクラス===================================

int LayerMapData::GOAL_FLASH_GRAPH = 0;

LayerMapData::LayerMapData(char* MapArray, int ChipNum) {

	if (!GOAL_FLASH_GRAPH) {
		GOAL_FLASH_GRAPH = LoadGraph("_resource/graphics/goalLight.png");
	}

	_chipNum = ChipNum;

	for (int y = 0; y < _chipNum; y++) {
		_initMapData.push_back(std::vector<char>());
		_copyFlash.push_back(std::vector<CopyEffect>());
		for (int x = 0; x < _chipNum; x++) {
			_initMapData[y].push_back(*(MapArray + y * _chipNum + x));
			_copyFlash[y].push_back(CopyEffect());
		}
	}

	_chipSize = GetWinSize().y / _chipNum;

	pal = 0;
	flag = false;
}

void LayerMapData::Init()
{
	_mapData = _initMapData;
	for (int y = 0; y < _chipNum; y++) {
		for (int x = 0; x < _chipNum; x++) {
			_copyFlash[y][x].TurnFalse();
		}
	}
}

void LayerMapData::Update(){
	for (int y = 0; y < _chipNum; y++) {
		for (int x = 0; x < _chipNum; x++) {
			_copyFlash[y][x].Update();
		}
	}

	if (!flag) {
		pal += GOAL_FLASH_SPEED;
		if (255 < pal) {
			pal = 255;
			flag = true;
		}
	}
	else {
		pal -= GOAL_FLASH_SPEED;
		if (pal < 0) {
			pal = 0;
			flag = false;
		}
	}
}

void LayerMapData::Draw(){
	for (int y = 0; y < _chipNum; y++) {
		for (int x = 0; x < _chipNum; x++) {
			int type = GetChipType(x, y);
			DrawExtendGraph(x * _chipSize, y * _chipSize, (x + 1) * _chipSize, (y + 1) * _chipSize, GRAPH[type], true);
			if (type == GOAL) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, pal);
				DrawExtendGraph(x * _chipSize, y * _chipSize, (x + 1) * _chipSize, (y + 1) * _chipSize, GOAL_FLASH_GRAPH, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			_copyFlash[y][x].Draw();
		}
	}
}

void LayerMapData::TransCopy(const std::vector<std::vector<char>>& MapData){
	for (int y = 0; y < _chipNum; y++) {
		for (int x = 0; x < _chipNum; x++) {
			if (MapData[y][x] != ZONE && MapData[y][x] != NONE
				&& this->_mapData[y][x] != WALL && this->_mapData[y][x] != ZONE) {
				//コピー元とコピー先が違ったら光らせる
				if (this->_mapData[y][x] != MapData[y][x]) {
					this->_copyFlash[y][x].Initialize({ x,y }, _chipSize);
				}
				this->_mapData[y][x] = MapData[y][x];
			}
			else if (MapData[y][x] == ZONE) {
				//コピー元とコピー先が違ったら光らせる
				if (this->_mapData[y][x] != MapData[y][x]) {
					this->_copyFlash[y][x].Initialize({ x,y }, _chipSize);
				}
				this->_mapData[y][x] = MapData[y][x];
			}
		}
	}
}

void LayerMapData::CopyCountUp(){
	for (int y = 0; y < _chipNum; y++) {
		for (int x = 0; x < _chipNum; x++) {
			_copyFlash[y][x].AddCount();
		}
	}
}


//ストック用マップデータクラス===================================
const float StockMapData::POSX= 1000 - 190.3 - 1.5 + (288.5 - (288.5 - 190.3) + 30);
const float StockMapData::POSY= (32 * 2 + (190.3 + 3) * 2) + 30;
const float StockMapData::FLASH_SPEED = DX_PI / 180 * 2;

void StockMapData::Init(float ChipSize){
	_empty = true;

	_chipSize = ChipSize;
	_chipNum = GetWinSize().y / _chipSize;

	for (int y = 0; y < _chipNum; y++) {
		_mapData.push_back(std::vector<char>());
		for (int x = 0; x < _chipNum; x++) {
			_mapData[y].push_back(0);
		}
	}

	pal = 0;
	radian = 0;
	old = false;
}

void StockMapData::Copy(LayerMapData& OriginalMap){
	this->_mapData = OriginalMap.GetMapData();
	_empty = false;
}

void StockMapData::Paste(LayerMapData& ToCopyMap){
	if (!_empty) {
		ToCopyMap.TransCopy(_mapData);
		_empty = true;
	}
}

void StockMapData::MiniMapDraw(){ 
	DrawGraph(POSX - 5, POSY - 6, COPY_STOCK_GRAPH, true);

	if (!_empty) {
		float size = 190.3 / _chipNum;
		for (int y = 0; y < _chipNum; y++) {
			for (int x = 0; x < _chipNum; x++) {
				DrawExtendGraph(POSX + x * size, POSY + y * size, POSX + (x + 1) * size, POSY + (y + 1) * size, GRAPH[GetChipType(x, y)], true);
			}
		}
	}
}

void StockMapData::Update(int PlayerOnChip)
{
	if (PlayerOnChip == PASTE_LAYER) {
		if (old != PASTE_LAYER) {
			radian = 0;
		}
		else {
			radian += FLASH_SPEED;
			if (DX_PI < radian) {
				radian = 0;
			}
		}
	}

	pal = sin(radian) * MAX_PAL;

	old = PlayerOnChip;
}

void StockMapData::Draw(const LayerMapData& NowMap)
{
	if (!_empty) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
		for (int y = 0; y < _chipNum; y++) {
			for (int x = 0; x < _chipNum; x++) {
				int type = GetChipType(x, y);
				int nowType = NowMap.GetChipType(x, y);
				if ((type != NONE && (type!=ZONE && nowType != WALL) && nowType != ZONE) || type == ZONE) {
					DrawExtendGraph(x * _chipSize, y * _chipSize, (x + 1) * _chipSize, (y + 1) * _chipSize, GRAPH[type], true);
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
