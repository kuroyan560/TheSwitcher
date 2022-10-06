#pragma once

//最大１０
static const int STAGE_ONE_MAP_NUM = 4;
static const int STAGE_TWO_MAP_NUM = 4;
static const int STAGE_THREE_MAP_NUM = 5;
static const int STAGE_FOUR_MAP_NUM = 5;
static const int STAGE_FIVE_MAP_NUM = 3;
static const int STAGE_SIX_MAP_NUM = 3;

/* 
	NONE = 0
	WALL = 1
	GOAL = 2
	GO_UPPER_LAYER = 3
	GO_LOWER_LAYER = 4
	COPY_LAYER = 5
	PASTE_LAYER = 6
	RESET_LAYER = 7
	ZONE = 8
*/

//ステージ１
char _mapLayer1_1[STAGE_ONE_MAP_NUM][STAGE_ONE_MAP_NUM] = {
	5,0,0,0,
	0,0,0,0,
	4,0,0,0,
	0,0,0,0
};

char _mapLayer1_2[STAGE_ONE_MAP_NUM][STAGE_ONE_MAP_NUM] = {
	0,0,1,2,
	0,0,1,0,
	0,0,1,0,
	3,0,0,0
};

char _mapLayer1_3[STAGE_ONE_MAP_NUM][STAGE_ONE_MAP_NUM] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};

char _mapLayer1_4[STAGE_ONE_MAP_NUM][STAGE_ONE_MAP_NUM] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};

char _mapLayer1_5[STAGE_ONE_MAP_NUM][STAGE_ONE_MAP_NUM] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
};

//ステージ２
char _mapLayer2_1[STAGE_TWO_MAP_NUM][STAGE_TWO_MAP_NUM] = {
	0,0,1,2,
	0,0,1,0,
	0,0,1,0,
	4,0,1,0
};

char _mapLayer2_2[STAGE_TWO_MAP_NUM][STAGE_TWO_MAP_NUM] = {
	0,0,0,0,
	6,0,0,0,
	0,0,0,0,
	3,4,0,0
};

char _mapLayer2_3[STAGE_TWO_MAP_NUM][STAGE_TWO_MAP_NUM] = {
	5,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,4,0,3
};

//ステージ３
char _mapLayer3_1[STAGE_THREE_MAP_NUM][STAGE_THREE_MAP_NUM] = {
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	6,0,0,0,0,
	4,0,0,0,0,
};

char _mapLayer3_2[STAGE_THREE_MAP_NUM][STAGE_THREE_MAP_NUM] = {
	0,0,2,0,0,
	0,0,0,0,0,
	1,1,1,1,1,
	0,0,0,0,0,
	4,3,0,0,0,
};

char _mapLayer3_3[STAGE_THREE_MAP_NUM][STAGE_THREE_MAP_NUM] = {
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,8,0,0,
	6,5,0,0,0,
	0,3,0,0,0,
};

//ステージ４
char _mapLayer4_1[STAGE_FOUR_MAP_NUM][STAGE_FOUR_MAP_NUM] = {
	0,0,6,0,4,
	0,0,0,0,0,
	6,8,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
};

char _mapLayer4_2[STAGE_FOUR_MAP_NUM][STAGE_FOUR_MAP_NUM] = {
	3,0,6,0,4,
	1,1,1,0,0,
	0,0,1,0,0,
	1,1,1,0,0,
	0,0,0,0,0
};

char _mapLayer4_3[STAGE_FOUR_MAP_NUM][STAGE_FOUR_MAP_NUM] = {
	3,0,5,6,0,
	0,1,1,1,0,
	0,1,8,1,0,
	0,1,8,1,0,
	0,0,0,0,0
};

char _mapLayer4_4[STAGE_FOUR_MAP_NUM][STAGE_FOUR_MAP_NUM] = {
	0,0,0,0,3,
	0,0,0,0,0,
	0,0,2,0,0,
	0,0,0,0,0,
	0,0,0,0,0
};

//ステージ５
char _mapLayer5_1[STAGE_FIVE_MAP_NUM][STAGE_FIVE_MAP_NUM] = {
	4,0,6,
	0,8,0,
	7,0,0
};

char _mapLayer5_2[STAGE_FIVE_MAP_NUM][STAGE_FIVE_MAP_NUM] = {
	8,0,3,
	1,1,1,
	4,8,0
};

char _mapLayer5_3[STAGE_FIVE_MAP_NUM][STAGE_FIVE_MAP_NUM] = {
	0,0,0,
	1,1,1,
	0,1,2
};

//ステージ６
char _mapLayer6_1[STAGE_SIX_MAP_NUM][STAGE_SIX_MAP_NUM] = {
	0,0,0,
	0,8,8,
	0,0,0
};
char _mapLayer6_2[STAGE_SIX_MAP_NUM][STAGE_SIX_MAP_NUM] = {
	8,0,0,
	8,0,0,
	0,0,0
};
char _mapLayer6_3[STAGE_SIX_MAP_NUM][STAGE_SIX_MAP_NUM] = {
	1,1,2,
	1,1,1,
	1,1,1
};
char _mapLayer6_4[STAGE_SIX_MAP_NUM][STAGE_SIX_MAP_NUM] = {
	0,0,0,
	0,0,0,
	3,8,8
};
char _mapLayer6_5[STAGE_SIX_MAP_NUM][STAGE_SIX_MAP_NUM] = {
	0,8,0,
	0,0,0,
	8,0,0
};