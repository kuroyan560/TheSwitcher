#pragma once
#include"Vector2.h"
#include<vector>
#include"Effect.h"

class MapData {
	static const int MAP_CHIP_GRAPH_SIZE = 64;

	static const int CHIP_TYPE_NUM = 9;
	static const char* GRAPH_PASS;

protected:
	static int GRAPH[CHIP_TYPE_NUM];
	static int COPY_STOCK_GRAPH;
	std::vector<std::vector<char>> _mapData;
	//マップチップ何×何か
	int _chipNum;
	float _chipSize;

public:
	static void Load();
	virtual ~MapData() {};
	virtual void MiniMapDraw(float Size, Vector2<float> LeftUpPos);
	//(y,x)番目のマップチップのデータ取得
	int GetChipType(int x, int y)const;

	std::vector<std::vector<char>> GetMapData() { return _mapData; }
};

class LayerMapData : public MapData{

private:
	static int GOAL_FLASH_GRAPH;
	static const int GOAL_FLASH_SPEED = 3;
	std::vector<std::vector<char>> _initMapData;
	std::vector<std::vector<CopyEffect>> _copyFlash;

	int pal;
	bool flag;

public:
	LayerMapData(char* MapArray,int ChipNum);
	~LayerMapData() {};

	void Init();
	void Update();
	virtual void Draw();

	//コピー転写（引数にコピー元）
	void TransCopy(const std::vector<std::vector<char>> &MapData);

	//コピーフラッシュカウントアップ
	void CopyCountUp();
};

class StockMapData : public MapData {
private:
	static const float POSX;
	static const float POSY;
	static const float FLASH_SPEED;
	static const int MAX_PAL = 130;
	bool _empty;
	int pal;
	float radian;
	int old;
public:
	StockMapData() { _empty = true; }
	~StockMapData() {};

	void Init(float ChipSize);
	void Copy(LayerMapData& OriginalMap);
	void Paste(LayerMapData& ToCopyMap);
	void MiniMapDraw();
	bool GetEmpty() { return _empty; }

	virtual void Update(int PlayerOnChip);
	virtual void Draw(const LayerMapData& NowMap);
};
