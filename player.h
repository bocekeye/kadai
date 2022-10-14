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

	bool isExist() { return m_isExist; }

private:

	int m_handle;

	//ショットの発射間隔
	int m_shotInterval;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	//表示位置
	Vec2 m_pos;

	//移動
	Vec2 m_vec;

	//存在するか
	bool  m_isExist;


};
