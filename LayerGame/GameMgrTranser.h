#pragma once
#include"MapData.h"
#include"Vector2.h"
//�Q�[���V�[���ɏ�����v������C���^�[�t�F�[�X
class GameMgrTranser{
public:
	virtual ~GameMgrTranser() {};

	virtual void CopyStock(LayerMapData& OriginalMap) = 0;
	virtual void PasteMap(LayerMapData& ToCopyMap) = 0;
	virtual void StockMiniMapDraw() = 0;
	virtual bool GetEmpty() = 0;
	virtual Vector2<int> PlayerPlace() = 0;
};