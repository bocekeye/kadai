#include "DxLib.h"
#include "Enemy.h"
#include "SceneMain.h"
#include <cassert>
#include <vector>

namespace
{
	constexpr int kShotInterval = 20;
}

void SceneMain::init()
{
	Vec2 pos;
	m_textPosX = 0;
	m_textVecX = 4;

	m_player.init();
	m_player.setMain(this);

	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	
	for (int i = 0; i < 1; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);
	
	//	pos.x = (i % 10) * 30.0f + 50.0f; //‚ ‚Ü‚è
	//	pos.y = (i / 10) * 30.0f + 50.0f;

		pos.x = (i % 10) * 30.0f + 310.0f;
		pos.y = (i / 10) * 30.0f + 100.0f;

		pEnemy->set(pos);
		m_pEnemyVt.push_back(pEnemy);
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
	m_player.update();

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

	std::vector<Shot*>::iterator it = m_pShotVt.begin();

	for (auto& pShot : m_pShotVt)
	{
		for (auto& pEnemy : m_pEnemyVt)
		{
			bool isHitShot = pShot->isCol(*pEnemy);
			bool isHitEnemy = pEnemy->isCol(*pShot);
			if (isHitShot) //isHit = true
			{
				pShot->shotDead();
			}
			if (isHitShot)
			{
				pEnemy->enemyDead();
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

	/*if (pEnemy->isCol(*pShot))
	{
		pEnemy->enemyDead();
	}*/
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
	m_player.draw();

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

}

//ƒvƒŒƒCƒ„[‚Ì’e‚Ì¶¬
bool SceneMain::createShot(Vec2 pos)
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


//for (auto& shot : m_pShotVt)
//{
//	Shot* pShot = static_cast<Shot*>(shot);

//	for (auto& enemy : m_pEnemyVt)
//	{
//		Enemy* pEnemy = static_cast<Enemy*>(enemy);

//		if (pShot->isCol(*pEnemy))
//		{
//			pShot->shotDead();								
//		}
//	/*	if (pEnemy->isCol(*pShot))
//		{
//			pEnemy->enemyDead();
//		}*/
//		if (pShot->isCol(*pEnemy))
//		{
//			DrawString(0, 45, "HIT!!!!!", GetColor(255, 255, 255));
//		}
//		else
//		{
//			DrawString(0, 60, "NO HIT", GetColor(255, 255, 255));

//		}
//	}
//}	