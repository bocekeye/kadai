#pragma once

#include "Vec2.h"

class Shot;

class SceneMain;

class Object
{
public:
	Object();
	virtual ~Object() {}

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }

	void init();

	void set(Vec2 pos);

	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void update();

	void draw();

//	void chageSize();

	bool isExist() { return m_isExist; }

	//弾との当たり判定
	bool isCol(Shot& shot);

	void objectDead();

	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	// グラフィックハンドル
	int m_handle;

	int m_hitCount;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 当たり判定の幅と高さ
	Vec2 m_colSize;

	//表示位置
	Vec2 m_pos;

	//存在するか
	bool  m_isExist;

};
