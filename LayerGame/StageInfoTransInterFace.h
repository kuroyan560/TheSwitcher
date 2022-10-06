#pragma once
#include"Vector2.h"

static enum ChipType {
	NONE, WALL, GOAL, 
	GO_UPPER_LAYER, GO_LOWER_LAYER,
	COPY_LAYER,PASTE_LAYER,
	RESET_LAYER,
	ZONE
};

//�X�e�[�W�̏����󂯎��C���^�[�t�F�[�X
class StageInfoTransInterFace {
public:
	virtual ~StageInfoTransInterFace() {};
	//�������p�֐�
	virtual Vector2<float> GetPlayerSpawnPos()const = 0;	//�v���C���[�������ʒu��n��

	//���󂯓n���֐��i�X�e�[�W����v���C���[�ցj
	virtual int GetMapData(Vector2<float> CenterPos) = 0;	//�}�b�v�f�[�^�擾

	//������v������֐��i�v���C���[����X�e�[�W�ցj
	virtual int PressSwitch(int WhatSwitch) = 0;

	//�S�[������
	virtual void ReachGoal() = 0;
};