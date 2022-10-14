#pragma once
#include "Vec2.h"

class Enemy;

class SceneMain;

class Shot
{
public:

	Shot();

	virtual ~Shot();

	void init();

	virtual void start(Vec2 pos);

	virtual void enemyStart(Vec2 pos);

	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();

	Vec2 getPos() const { return m_pos; }

	Vec2 getColSize() const { return m_colSize; }

	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	//���݂��邩
	bool isExist() const { return m_isExist; }

	//�G�Ƃ̏Փ˔���
	bool isCol(Enemy& enemy);

protected:

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;

	//���݂��邩
	bool    m_isExist;

};



