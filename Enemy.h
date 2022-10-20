#include "Vec2.h"

class Player;

class Shot;

class SceneMain;

class Enemy
{
public:

	Enemy();
	virtual ~Enemy() {}

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }

	void init();

	void set(Vec2 pos); 

	void end();

	void update();

	void draw();

	bool isExist() { return m_isExist; }

	//弾との当たり判定
	bool isCol(Shot& shot);

	bool isCompare(Player& player);

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

	// グラフィックハンドル
	int m_handle;

	//移動間隔
	int m_waitFrame;

	//左右移動
	int m_slide;

	//左右移動の上限設定
	int m_moveCount;

	//敵の攻撃間隔
	int m_enemyShotInterval;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	//表示位置
	Vec2 m_pos;

	//移動
	Vec2 m_vec;

	// 当たり判定の幅と高さ
	Vec2 m_colSize;

	//存在するか
	bool  m_isExist;

};