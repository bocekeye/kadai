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
	// 更新
	virtual void update();
	// 表示
	virtual void draw();

	Vec2 getPos() const { return m_pos; }

	//float getLeft() const { return m_pos.x; }
	//float getRight() const { return m_pos.x + m_size.x; }
	//float getUp() const { return m_pos.y; }
	//float getBottom() const { return m_pos.y + m_pos.y; }


	//存在するか
	bool isExist() const { return m_isExist; }

	//敵との衝突判定
	bool isCol(Enemy& enemy);

protected:

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;

	//存在するか
	bool    m_isExist;

};



