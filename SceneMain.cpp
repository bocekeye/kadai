#include "DxLib.h"

#include "Enemy.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneFailResult.h"

#include "game.h"

#include <cassert>
#include <vector>

namespace
{
	//敵の数
	constexpr int kEnemyNum = 30;
}

void SceneMain::init()
{
	//グラフィックハンドルのロード
	m_hPlayerGraghic = LoadGraph("data/player.png");
	m_hEnemyGraghic = LoadGraph("data/enemy.png");
	m_hPlayerShotGraghic = LoadGraph("data/playerShot.png");
	m_hEnemyShotGraghic = LoadGraph("data/enemyShot.png");
	m_hObjectGrahic = LoadGraph("data/object.png");

	Vec2 pos;

	Player* pPlayer = new Player;
	pPlayer->init();
	pPlayer->setHandle(m_hPlayerGraghic);
	pPlayer->setMain(this);
	m_pPlayerVt.push_back(pPlayer);

	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	
	//敵の生成
	for (int i = 0; i < kEnemyNum; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setHandle(m_hEnemyGraghic);
		pEnemy->setMain(this);
	
		pos.x = static_cast<float>(i % 10) * 60.0f + 100.0f; //あまり
		pos.y = static_cast<float>(i / 10) * 60.0f + 50.0f;

		pEnemy->set(pos);
		m_pEnemyVt.push_back(pEnemy);
	}
	
	//オブジェクトの生成
	for (int i = 0; i < 4; i++)
	{
		Object* pObject = new Object;
		pObject->init();
		pObject->setHandle(m_hObjectGrahic);
		
		pObject->setMain(this);

		pos.x = static_cast<float>(i % 5) * 150.0f + 120.0f;
		pos.y = 400.0f;

		pObject->set(pos);
		m_pObjectVt.push_back(pObject);
	}
}

void SceneMain::end()
{
	//グラフィックアンロード
	DeleteGraph(m_hPlayerGraghic);
	DeleteGraph(m_hEnemyGraghic);
	DeleteGraph(m_hPlayerShotGraghic);
	DeleteGraph(m_hEnemyShotGraghic);
	DeleteGraph(m_hObjectGrahic);

	for (auto& pPlayer : m_pPlayerVt)
	{
		assert(pPlayer);

		delete pPlayer;
		pPlayer = nullptr;
	}

	for (auto& pEnemy : m_pEnemyVt)
	{
		assert(pEnemy);

		delete pEnemy;
		pEnemy = nullptr;
	}

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}

	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);

		delete pObject;
		pObject = nullptr;
	}
}

SceneBase* SceneMain::update()
{
	//プレイヤー
	for (auto& pPlayer : m_pPlayerVt)
	{
		assert(pPlayer);
		pPlayer->update();
	}
	//敵
	for (auto& pEnemy : m_pEnemyVt)
	{
		assert(pEnemy);
		pEnemy->update();
	}
	//弾
	std::vector<Shot*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update();

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除
			it = m_pShotVt.erase(it); //eraseは削除した次の要素を返してくれる
			continue;
		}
		it++;
	}

	//オブジェクト
	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);
		pObject->update();
	}


	for (auto& pShot : m_pShotVt)
	{
		for (auto& pEnemy : m_pEnemyVt)
		{
			for (auto& pPlayer : m_pPlayerVt)
			{
				for (auto& pObject : m_pObjectVt)
				{
					bool isHitShot = pShot->isCol(*pEnemy);    //弾が敵に当たると弾が消える
					bool isHitEnemy = pEnemy->isCol(*pShot);   //弾が敵に当たると敵が消える
					bool isHitPlayer = pPlayer->isCol(*pShot); //弾がプレイヤーに当たるとプレイヤーが消える
					bool isHitObject = pObject->isCol(*pShot); //弾がオブジェクトに当たるとオブジェクトが消える
					bool isCompareEnemy = pEnemy->isCompare(*pPlayer);
					if (isHitShot) //isHit = true
					{
						pShot->shotDead();
					}
					if (isHitEnemy)
					{	
						Vec2 pos;
						pEnemy->enemyDead();

						//敵を全部倒したらクリア画面に行く
						m_hitEnemyCount++;
						if (m_hitEnemyCount >= kEnemyNum)
						{
							return (new SceneResult);
							m_hitEnemyCount = 0;
						}	
					}
					if (isHitPlayer)
					{
						pPlayer->playerDead();
						pShot->shotDead();
						
						//プレイヤーが死んだら失敗画面に行く
						return (new SceneFailResult);
					}
					if (isHitObject)
					{	
						//オブジェクトに15回弾が当たると消える
						m_hitObjectCount++;
						if (m_hitObjectCount >= 15)
						{
							pObject->objectDead();
							m_hitObjectCount = 0;
						}
					//	pObject->chageSize(); //オブジェクトのサイズが小さくなる
						pShot->shotDead();    //オブジェクトに弾が当たると弾が消える
					}
					if (isCompareEnemy)
					{
						return (new SceneFailResult);
					}
					//デバック用
					/*if (isHitShot)
					{
						DrawString(0, 45, "HIT!!!!!", GetColor(255, 255, 255));
					}
					else
					{
						DrawString(0, 60, "NO HIT", GetColor(255, 255, 255));
					}	*/
				}		
			}
		}	
	}
	
	return this;
}

//描画
void SceneMain::draw()
{
	for (auto& pPlayer : m_pPlayerVt)
	{
		assert(pPlayer);
		pPlayer->draw();
	}

	for (auto& pEnemy : m_pEnemyVt)
	{
		assert(pEnemy);
		pEnemy->draw();
	}

//	DrawFormatString(0, 30, GetColor(255, 255, 255), "敵の数:%d", m_pEnemyVt.size());

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//存在している弾の数の表示
//	DrawFormatString(0, 15, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());

	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);
		pObject->draw();
	}

	DrawString(160,10, "-----キーボードはXまたはPADはAで弾を発射できます-----", GetColor(255, 255, 255));
}


//プレイヤーの弾の生成
bool SceneMain::playerShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->start(pos);
	pShot->setHandle(m_hPlayerShotGraghic);
	pShot->shotConfirPlayer(true);
	m_pShotVt.push_back(pShot);

	return true;
}

//敵の弾の生成
bool SceneMain::enemyShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->enemyStart(pos);
	pShot->setHandle(m_hEnemyShotGraghic);
	pShot->shotConfirPlayer(false);
	m_pShotVt.push_back(pShot);

	return true;
}

//一番下の敵のみに弾を打たせる
bool SceneMain::isCheckEnemyShot(Vec2 shotPos) //pos = 弾の発射位置
{
	for (auto& pEnemy : m_pEnemyVt)
	{
		if (shotPos.y > pEnemy->getBottom()) continue;      //弾より上に敵がいた場合チェックしない
		if (shotPos.x > pEnemy->getLeft())   continue;      //弾より左に敵がいた場合チェックしない
		if (shotPos.x < pEnemy->getRight())  continue;      //弾より右に敵がいた場合チェックしない

		return false;
	}
	return true;
}
