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

	//敵のサイズ
	void setSize(Vec2 size) { m_size = size; }

	bool isExist() { return m_isExist; }

	//弾との当たり判定
	bool isCol(Shot& shot);

	void enemyDead();

	//当たり判定の座標
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	//SceneMainのポインタ
	SceneMain* m_pMain;

	Vec2 m_size;

	Vec2 m_pos;

	Vec2 m_vec;

	// 当たり判定の幅と高さ
	Vec2 m_colSize;

	//移動間隔
	int m_waitFrame;

	//敵の攻撃間隔
	int m_enemyShotInterval;

	//存在するか
	bool  m_isExist;

};