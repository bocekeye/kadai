#include "Vec2.h"

class Player;

class Shot;

class SceneMain;

class Enemy
{
public:

	Enemy();
	virtual ~Enemy() {}

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	void init();

	void set(Vec2 pos); 

	void end();

	void update();

	void draw();

	bool isExist() { return m_isExist; }

	//�e�Ƃ̓����蔻��
	bool isCol(Shot& shot);

	bool isCompare(Player& player);

	void enemyDead();

	//�����蔻��̍��W
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }    
	float getBottom() const { return m_pos.y + m_colSize.y; }

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	// �O���t�B�b�N�n���h��
	int m_handle;

	//�ړ��Ԋu
	int m_waitFrame;

	//���E�ړ�
	int m_slide;

	//���E�ړ��̏���ݒ�
	int m_moveCount;

	//�G�̍U���Ԋu
	int m_enemyShotInterval;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	//�\���ʒu
	Vec2 m_pos;

	//�ړ�
	Vec2 m_vec;

	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	//���݂��邩
	bool  m_isExist;

};