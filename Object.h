#pragma once

#include "Vec2.h"

class Shot;

class SceneMain;

class Object
{
public:
	Object();
	virtual ~Object() {}

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	void init();

	void set(Vec2 pos);

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void update();

	void draw();

//	void chageSize();

	bool isExist() { return m_isExist; }

	//�e�Ƃ̓����蔻��
	bool isCol(Shot& shot);

	void objectDead();

	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	// �O���t�B�b�N�n���h��
	int m_handle;

	int m_hitCount;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	//�\���ʒu
	Vec2 m_pos;

	//���݂��邩
	bool  m_isExist;

};
