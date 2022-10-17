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

	Player* pPlayer = new Player;
	pPlayer->init();
	pPlayer->setMain(this);
	m_pPlayerVt.push_back(pPlayer);
	//m_player.init();
	//m_player.setMain(this);

	Shot* pShot = new Shot;
	pShot->init();
	pShot->setMain(this);
	
	for (int i = 0; i < 1; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);
	
	//	pos.x = (i % 10) * 30.0f + 50.0f; //���܂�
	//	pos.y = (i / 10) * 30.0f + 50.0f;

		pos.x =static_cast<float>(i % 10) * 30.0f + 310.0f;
		pos.y = static_cast<float>(i / 10) * 30.0f + 100.0f;

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
	for (auto& pPlayer : m_pPlayerVt)
	{
		assert(pPlayer);
		pPlayer->update();
	}
//	m_player.update();

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
			for (auto& pPlayer : m_pPlayerVt)
			{
				bool isHitShot = pShot->isCol(*pEnemy); //�e���G�ɓ�����ƒe��������
				bool isHitEnemy = pEnemy->isCol(*pShot); //�e���G�ɓ�����ƓG��������
				bool isHitPlayer = pPlayer->isCol(*pShot); //�G�̒e���v���C���[�ɓ�����ƃv���C���[��������
				if (isHitShot) //isHit = true
				{
					pShot->shotDead();
				}
				if (isHitShot)
				{
					pEnemy->enemyDead();
				}
				if (isHitPlayer)
				{
				//	pPlayer->playerDead();
				}
				//�f�o�b�N�p
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

	
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it); //erase�͍폜�������̗v�f��Ԃ��Ă����
			continue;
		}
		it++;
	}

}

void SceneMain::draw()
{
	DrawString(m_textPosX, 0, "���C�����", GetColor(255, 255, 255));
//	m_player.draw();

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
	DrawFormatString(0, 30, GetColor(255, 255, 255), "�G�̐�:%d", m_pEnemyVt.size());


	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		pShot->draw();
	}
	//���݂��Ă���e�̐��̕\��
	DrawFormatString(0, 15, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());

}

//�v���C���[�̒e�̐���
bool SceneMain::playerShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->start(pos);
	pShot->shotConfirPlayer(true);
	m_pShotVt.push_back(pShot);

	return true;
}

//�G�̒e�̐���
bool SceneMain::enemyShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->init();
	pShot->enemyStart(pos);
	pShot->shotConfirPlayer(false);
	m_pShotVt.push_back(pShot);

	return true;
}
