#pragma once

#include "Vec2.h"

class Shot;

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player(){}

	// グラフィックデータ設定
//	void setHandle(int handle) { m_handle = handle; }

	void init();
	
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void update();

	void draw();

	bool isExist() { return m_isExist; }

	//弾との当たり判定
	bool isCol(Shot& shot);

	void playerDead();

	//当たり判定の座標
	float getLeft() const { return m_pos.x; }
	float getRight() const { return m_pos.x + m_colSize.x; }
	float getUp() const { return m_pos.y; }
	float getBottom() const { return m_pos.y + m_colSize.y; }

	Vec2 getPos() const { return m_pos; }
	Vec2 getColSize() const { return m_colSize; }

private:

	int m_handle;

	//ショットの発射間隔
	int m_shotInterval;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 当たり判定の幅と高さ
	Vec2 m_colSize;

	//表示位置
	Vec2 m_pos;

	//移動
	Vec2 m_vec;

	//存在するか
	bool  m_isExist;


};
