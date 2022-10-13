#include "DxLib.h"

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

	m_shot.setMain(this);
	
	for (int i = 0; i < 15; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);
	
		pos.x = (i % 5) * 30 + 30; //あまり
		pos.y = (i / 5) * 30 + 50;


		pEnemy->set(pos);

		m_pEnemyVt.push_back(pEnemy);
	}

	for (int i = 0; i < 15; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);

		pos.x = (i % 5) * 30 + 200; //あまり
		pos.y = (i / 5) * 30 + 50;


		pEnemy->set(pos);

		m_pEnemyVt.push_back(pEnemy);
	}
	for (int i = 0; i < 15; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);

		pos.x = (i % 5) * 30 + 370; //あまり
		pos.y = (i / 5) * 30 + 50;


		pEnemy->set(pos);

		m_pEnemyVt.push_back(pEnemy);
	}

	
	/*m_enemy.init();
	m_enemy.setMain(this);*/

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
//	m_enemy.update();

	for (auto& pEnemy : m_pEnemyVt)
	{
		assert(pEnemy);

		pEnemy->update();
	}



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
}

void SceneMain::draw()
{
	DrawString(m_textPosX, 0, "メイン画面", GetColor(255, 255, 255));
	m_player.draw();
	m_enemy.draw();

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
}

bool SceneMain::createShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}


