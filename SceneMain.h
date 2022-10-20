#pragma once
#include "SceneBase.h"
#include "shot.h"
#include "player.h"
#include "Object.h"
#include <vector>

class Enemy;

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_textPosX = 0;
		m_textVecX = 0;
		m_hitEnemyCount = 0;
		m_hitObjectCount = 0;
		m_isEnd = false;
	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end() {}

	virtual SceneBase* update() override;

	virtual void draw();

	//プレイヤーのショットの生成
	bool playerShot(Vec2 pos);
	//敵のショットの生成
	bool enemyShot (Vec2 pos);

	//一番下にいる敵が弾を打てるかどうか
	bool isCheckEnemyShot(Vec2 pos);

	virtual bool isEnd() { return m_isEnd; }
private:
	// テキスト表示位置変更
	int m_textPosX;
	int m_textVecX;

	int m_hitEnemyCount; //敵に弾が当たった時のカウント
	int m_hitObjectCount; //オブジェクトに弾が当たった時のカウント

	bool m_isEnd;

	//プレイヤー
	Player m_player;

	std::vector<Object*> m_pObjectVt;
	std::vector<Player*> m_pPlayerVt;
	std::vector<Shot*>   m_pShotVt;
	std::vector<Enemy*>  m_pEnemyVt;
};