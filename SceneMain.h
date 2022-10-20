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
		m_hitEnemyCount = 0;
		m_hitObjectCount = 0;
		m_hitEnemyCount = 0;
		m_hitObjectCount = 0;
		m_hObjectGrahic = -1;

		m_hPlayerGraghic = -1;
		m_hEnemyGraghic = -1;
		m_hPlayerShotGraghic = -1;
		m_hEnemyShotGraghic = -1;
		m_hObjectGrahic = -1;

	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;

	virtual void draw();

	//プレイヤーのショットの生成
	bool playerShot(Vec2 pos);
	//敵のショットの生成
	bool enemyShot (Vec2 pos);

	//一番下にいる敵が弾を打てるかどうか
	bool isCheckEnemyShot(Vec2 pos);

//	virtual bool isEnd() { return m_isEnd; }
private:
	// テキスト表示位置変更
	int m_textPosX;
	int m_textVecX;

	int m_hitEnemyCount; //敵に弾が当たった時のカウント
	int m_hitObjectCount; //オブジェクトに弾が当たった時のカウント

	//プレイヤーグラフィックハンドル
	int m_hPlayerGraghic;
	int m_hEnemyGraghic;
	int m_hPlayerShotGraghic;
	int m_hEnemyShotGraghic;
	int m_hObjectGrahic;

	//プレイヤー
	Player m_player;

	std::vector<Object*> m_pObjectVt;
	std::vector<Player*> m_pPlayerVt;
	std::vector<Shot*>   m_pShotVt;
	std::vector<Enemy*>  m_pEnemyVt;
};