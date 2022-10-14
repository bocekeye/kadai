#include "Vec2.h"

class SceneMain;

class Enemy
{
public:

	Enemy();
	virtual ~Enemy();

	void init();

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void set(Vec2 pos);

	void end();

	void update();

	
	void draw();

	//�G�̃T�C�Y
	void setSize(Vec2 size) { m_size = size; }

	//�G�̃V���b�g
	void addEnemyShot(Vec2 pos);

	Vec2 getPos() const { return m_pos; }

	bool isExist() const { return m_isExist; }

	Vec2 getColSize() const { return m_colSize; }
	
	//�����蔻��̍��W
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_size.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const{ return m_pos.y + m_pos.y; }
 
private:

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	Vec2 m_size;

	Vec2 m_pos;

	Vec2 m_vec;

	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	//�ړ��Ԋu
	int m_waitFrame;

	//�G�̍U���Ԋu
	int m_enemyShotInterval;

	//���݂��邩
	bool    m_isExist;



};