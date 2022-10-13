#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player(){};

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }

	void init();
	
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	void update();

	void draw();

	Vec2 getPos() const { return m_pos; }

private:

	int m_handle;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	//表示位置
	Vec2 m_pos;
	//移動
	Vec2 m_vec;

	//ショットの発射間隔
	int m_shotInterval;

};
