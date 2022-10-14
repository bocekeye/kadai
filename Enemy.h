#include "Vec2.h"

class Shot;

class SceneMain;

class Enemy
{
public:

	Enemy();
	virtual ~Enemy();

	void init();

	void set(Vec2 pos);

	void end();

	void update();

	void draw();

	//“G‚ÌƒTƒCƒY
	void setSize(Vec2 size) { m_size = size; }

	bool isExist() { return m_isExist; }

	//’e‚Æ‚Ì“–‚½‚è”»’è
	bool isCol(Shot& shot);

	void enemyDead();

	//“–‚½‚è”»’è‚ÌÀ•W
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	//SceneMain‚Ìƒ|ƒCƒ“ƒ^
	SceneMain* m_pMain;

	Vec2 m_size;

	Vec2 m_pos;

	Vec2 m_vec;

	// “–‚½‚è”»’è‚Ì•‚Æ‚‚³
	Vec2 m_colSize;

	//ˆÚ“®ŠÔŠu
	int m_waitFrame;

	//“G‚ÌUŒ‚ŠÔŠu
	int m_enemyShotInterval;

	//‘¶İ‚·‚é‚©
	bool  m_isExist;

};