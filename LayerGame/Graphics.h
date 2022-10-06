#pragma once
#include"Vector2.h"
//基底クラス
class Graphics
{
protected:
	bool transFlag;

public:
	virtual ~Graphics() {};
	virtual void Draw(Vector2<float> Position, Vector2<float> Size, bool Turn = false) = 0;	//左上座標
};

//点滅機能
class Flash
{
protected:
	Flash(int Span,int Count);
	~Flash() {};

	int flashSpan;
	int timer;
	int countMax;
	int counter;

	void StartFlash();	//点滅スタート
};

//ループ＆透明度変更しない画像========================================
class Image :public Graphics
{
protected:
	int handle;

public:
	Image(const char* FileName,bool Trans);
	~Image() {};

	virtual void Draw(Vector2<float> Position, Vector2<float> Size, bool Turn = false)override;
};
//点滅機能つき
class FlashImage :public Image,Flash
{
public:
	FlashImage(const char* FileName, bool Trans, int Span, int Count);
	~FlashImage() {};

	virtual void Draw(Vector2<float> Position, Vector2<float> Size, bool Turn = false)override;
};

//ループする画像======================================================
class LoopImage :public Graphics
{
protected:
	static int flame;
	int maxFlame;		//画像の枚数
	int speed;
	int* arrayPtr;

public:
	static void FlameUpdate();

	LoopImage(const char* FileName, bool Trans, int MaxFlame, int Speed, Vector2<int> num, Vector2<float> size);
	LoopImage() {};
	~LoopImage();

	void Init(const char* FileName, bool Trans, int MaxFlame, int Speed, Vector2<int> num, Vector2<float> size);
	virtual void Draw(Vector2<float> Position, Vector2<float> Size, bool Turn = false)override;
};

//アニメーションする画像
class AnimationImage : public Graphics
{
private:
	int maxFlame;		//画像の枚数
	int* arrayPtr;
	int flame;
	int lastDrawFlame;
	int speed;
	bool animationFlag;
	int timer;
	bool imageSwitchFlag;
	bool firstFlameDraw;

public:
	AnimationImage(const char* FileName, bool Trans, int MaxFlame, int Speed,Vector2<int> num, 
				   Vector2<float> size, int LastDrawFlame, bool ImageSwitchFlag, bool firstFlame = false);
	AnimationImage() {};
	~AnimationImage() {};

	void Init();
	void Init(const char* FileName, bool Trans, int MaxFlame, int Speed, Vector2<int> num, 
			  Vector2<float> size, int LastDrawFlame, bool ImageSwitchFlag, bool firstFlame = false);
	void Update();
	virtual void Draw(Vector2<float> Position, Vector2<float> Size, bool Turn = false)override;

	void AnimationStart();
	bool NowAnimation()const { return animationFlag; }
	bool DrawComplete();
};

//点滅機能つき
class FlashLoopImage :public LoopImage,Flash
{
public:
	FlashLoopImage(const char* FileName, bool Trans, int MaxFlame, int Speed, 
						Vector2<int> num, Vector2<float> size, int Span, int Count);
	~FlashLoopImage() {};
	
	virtual void Draw(Vector2<float> Position, Vector2<float> Size, bool Turn = false)override;
};