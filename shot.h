#pragma once
#include "Vec2.h"
#include "Enemy.h"
class SceneMain;

class Shot
{
public:

	Shot();

	virtual ~Shot();

	void init();

	virtual void start(Vec2 pos);

	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();

	Vec2 getPos() const { return m_pos; }

	//float getLeft() const { return m_pos.x; }
	//float getRight() const { return m_pos.x + m_size.x; }
	//float getUp() const { return m_pos.y; }
	//float getBottom() const { return m_pos.y + m_pos.y; }


	//���݂��邩
	bool isExist() const { return m_isExist; }

	//�G�Ƃ̏Փ˔���
	bool isCol(Enemy& enemy);

protected:

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;

	//���݂��邩
	bool    m_isExist;

};



