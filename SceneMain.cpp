#include "DxLib.h"
#include "Enemy.h"
#include "SceneMain.h"
#include <cassert>
#include <vector>

namespace
{
//	constexpr int kShotInterval = 20;
}

void SceneMain::init()
{
	Vec2 pos;
	m_textPosX = 0;
	m_textVecX = 4;
	Player* pPlayer = new Player;
	pPlayer->init();
	pPlayer->setMain(this);
	m_pPlayerVt.push_back(pPlayer);

	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	
	for (int i = 0; i < 30; i++)	
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);
	
		pos.x = static_cast<float>(i % 10) * 65.0f + 100.0f;
		pos.y = static_cast<float>(i / 10) * 65.0f + 50.0f;

		pEnemy->set(pos);
		m_pEnemyVt.push_back(pEnemy);
	}

	for (int i = 0; i < 4; i++)
	{
		Object* pObject = new Object;
		pObject->init();
		pObject->setMain(this);

		pos.x = static_cast<float>(i % 10) * 170.0f + 100.0f;
		pos.y = 400.0f;

		pObject->set(pos);
		m_pObjectVt.push_back(pObject);
	}
}

//void SceneMain::end()
//{
//	for (auto& pShot : m_pShotVt)
//	{
//		assert(pShot);
//
//		delete pShot;
//		pShot = nullptr;
//	}
//
//}

void SceneMain::update()
{
	for (auto& pPlayer : m_pPlayerVt)
	{
		assert(pPlayer);
		pPlayer->update();
	}

	for (auto& pEnemy : m_pEnemyVt)
	{
		assert(pEnemy);
		pEnemy->update();
	}

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->update();
	}

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
					bool isHitShot = pShot->isCol(*pEnemy);    //’e‚ª“G‚É“–‚½‚é‚Æ’e‚ªÁ‚¦‚é
					bool isHitEnemy = pEnemy->isCol(*pShot);   //’e‚ª“G‚É“–‚½‚é‚Æ“G‚ªÁ‚¦‚é
					bool isHitPlayer = pPlayer->isCol(*pShot); //’e‚ªƒvƒŒƒCƒ„[‚É“–‚½‚é‚ÆƒvƒŒƒCƒ„[‚ªÁ‚¦‚é
					bool isHitObject = pObject->isCol(*pShot);
					if (isHitShot) //isHit = true
					{
						pShot->shotDead();
					}
					if (isHitEnemy)
					{
						pEnemy->enemyDead();
					}
					if (isHitPlayer)
					{
						/*pPlayer->playerDead();
						pShot->shotDead();*/
					}
					if (isHitObject)
					{
						pObject->objectDead();
						pShot->shotDead();
					}
					//ƒfƒoƒbƒN—p
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

			//vector‚Ì—v‘fíœ
			it = m_pShotVt.erase(it); //erase‚Ííœ‚µ‚½ŽŸ‚Ì—v‘f‚ð•Ô‚µ‚Ä‚­‚ê‚é
			continue;
		}
		it++;
	}
}

void SceneMain::draw()
{
	DrawString(m_textPosX, 0, "ƒƒCƒ“‰æ–Ê", GetColor(255, 255, 255));

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
	DrawFormatString(0, 30, GetColor(255, 255, 255), "“G‚Ì”:%d", m_pEnemyVt.size());


	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//‘¶Ý‚µ‚Ä‚¢‚é’e‚Ì”‚Ì•\Ž¦
	DrawFormatString(0, 15, GetColor(255, 255, 255), "’e‚Ì”:%d", m_pShotVt.size());

	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);
		pObject->draw();
	}
}

//ƒvƒŒƒCƒ„[‚Ì’e‚Ì¶¬
bool SceneMain::playerShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->start(pos);
	pShot->shotConfirPlayer(true);
	m_pShotVt.push_back(pShot);

	return true;
}

//“G‚Ì’e‚Ì¶¬
bool SceneMain::enemyShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->enemyStart(pos);
	pShot->shotConfirPlayer(false);
	m_pShotVt.push_back(pShot);

	return true;
}
