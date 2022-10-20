#include "DxLib.h"
#include <cassert>
#include <vector>

#include "Enemy.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneFailResult.h"

namespace
{
	//敵の数
	constexpr int kEnemyNum = 30;
}

void SceneMain::init()
{
	Vec2 pos;
	m_hitEnemyCount = 0;
	m_hitObjectCount = 0;
	m_isEnd = false;

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
		pEnemy->setMain(this);
	
		pos.x = static_cast<float>(i % 10) * 65.0f + 100.0f; //あまり
		pos.y = static_cast<float>(i / 10) * 65.0f + 50.0f;

		pEnemy->set(pos);
		m_pEnemyVt.push_back(pEnemy);
	}
	
	//オブジェクトの生成
	for (int i = 0; i < 4; i++)
	{
		Object* pObject = new Object;
		pObject->init();
		pObject->setMain(this);

		pos.x = static_cast<float>(i % 5) * 170.0f + 100.0f;
		pos.y = 400.0f;

		pObject->set(pos);
		m_pObjectVt.push_back(pObject);
	}

	//グラフィックハンドルのロード
	m_hPlayerGraghic = LoadGraph("data/player.jpeg");

}

void SceneMain::end()
{
	DeleteGraph(m_hPlayerGraghic);
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
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->update();
	}
	//オブジェクト
	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);
		pObject->update();
	}

	std::vector<Shot*>::iterator it = m_pShotVt.begin();

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
					if (isHitShot) //isHit = true
					{
						pShot->shotDead();
					}
					if (isHitEnemy)
					{	
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
						//オブジェクトに10回弾が当たると消える
						m_hitObjectCount++;
						if (m_hitObjectCount >= 10)
						{
							pObject->objectDead();
							m_hitObjectCount = 0;
						}
						pObject->chageSize(); //オブジェクトのサイズが小さくなる
						pShot->shotDead();    //オブジェクトに弾が当たると弾が消える
					}
					//デバック用
					if (isHitShot)
					{
						DrawString(0, 45, "HIT!!!!!", GetColor(255, 255, 255));
					}
					else
					{
						DrawString(0, 60, "NO HIT", GetColor(255, 255, 255));
					}	
				}		
			}
		}	
	}

	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

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
	return this;
}

//描画
void SceneMain::draw()
{
//	DrawString(m_textPosX, 0, "メイン画面", GetColor(255, 255, 255));

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

	DrawFormatString(0, 30, GetColor(255, 255, 255), "敵の数:%d", m_pEnemyVt.size());

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//存在している弾の数の表示
	DrawFormatString(0, 15, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());

	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);
		pObject->draw();
	}
}

//プレイヤーの弾の生成
bool SceneMain::playerShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->start(pos);
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
