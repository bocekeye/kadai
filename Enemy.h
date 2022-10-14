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

	//敵のサイズ
	void setSize(Vec2 size) { m_size = size; }

	//敵のショット
	void addEnemyShot(Vec2 pos);

	Vec2 getPos() const { return m_pos; }

	bool isExist() const { return m_isExist; }

	Vec2 getColSize() const { return m_colSize; }
	
	//当たり判定の座標
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_size.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const{ return m_pos.y + m_pos.y; }
 
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
	bool    m_isExist;



};