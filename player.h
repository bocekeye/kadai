#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player(){};

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	void init();
	
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void update();

	void draw();

	Vec2 getPos() const { return m_pos; }

private:

	int m_handle;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	//�\���ʒu
	Vec2 m_pos;
	//�ړ�
	Vec2 m_vec;

	//�V���b�g�̔��ˊԊu
	int m_shotInterval;

};