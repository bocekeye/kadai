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

	
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();

	//���݂��邩
	bool isExist() const { return m_isExist; }

	//�G�Ƃ̓����蔻��
	bool isCol(Enemy& enemy);


	void shotDead();

	//�����蔻��̍��W�擾
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void shotConfirPlayer(bool isPlayer){m_isPlayer = isPlayer;} //�v���C���[�����ʂ��G���łʂ��̊m�F
	bool getShotPlayer() const { return m_isPlayer; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

protected:

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;

	bool m_isPlayer;

	//���݂��邩
	bool m_isExist;

};



