#pragma once

#include "Vec2.h"

class Shot;

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player(){}

	// �O���t�B�b�N�f�[�^�ݒ�
//	void setHandle(int handle) { m_handle = handle; }

	void init();
	
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void update();

	void draw();

	bool isExist() { return m_isExist; }

	//�e�Ƃ̓����蔻��
	bool isCol(Shot& shot);

	void playerDead();

	//�����蔻��̍��W
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	int m_handle;

	//�V���b�g�̔��ˊԊu
	int m_shotInterval;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	//�\���ʒu
	Vec2 m_pos;

	//�ړ�
	Vec2 m_vec;

	//���݂��邩
	bool  m_isExist;


};
