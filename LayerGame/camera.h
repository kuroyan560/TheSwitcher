#pragma once
class Camera{
private:
	static const float CHANGE_RATE;
	static const float SCROLL_CHANGE_RATE;
	float oldPosX;
	float posX;
	float toX;
	float rate;
	bool firstScroll;

public:
	Camera();
	~Camera();

	void Init(const int MaxStageNum,const int NowStage);
	void Update();

	//float GetCamRate()const { return rate; }
	bool NowScroll();
	bool CanInputSelect();
	float GetScrollX() { return posX; }
	void MoveSet(const int& NowSelect);
};

