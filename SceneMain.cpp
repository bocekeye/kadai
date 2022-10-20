#include "DxLib.h"
#include <cassert>
#include <vector>

#include "Enemy.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneFailResult.h"

namespace
{
	//�G�̐�
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
	
	//�G�̐���
	for (int i = 0; i < kEnemyNum; i++)
	{
		Enemy* pEnemy = new Enemy;
		pEnemy->init();
		pEnemy->setMain(this);
	
		pos.x = static_cast<float>(i % 10) * 65.0f + 100.0f; //���܂�
		pos.y = static_cast<float>(i / 10) * 65.0f + 50.0f;

		pEnemy->set(pos);
		m_pEnemyVt.push_back(pEnemy);
	}
	
	//�I�u�W�F�N�g�̐���
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

	//�O���t�B�b�N�n���h���̃��[�h
	m_hPlayerGraghic = LoadGraph("data/player.jpeg");

}

void SceneMain::end()
{
	DeleteGraph(m_hPlayerGraghic);
}

SceneBase* SceneMain::update()
{
	//�v���C���[
	for (auto& pPlayer : m_pPlayerVt)
	{
		assert(pPlayer);
		pPlayer->update();
	}
	//�G
	for (auto& pEnemy : m_pEnemyVt)
	{
		assert(pEnemy);
		pEnemy->update();
	}
	//�e
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->update();
	}
	//�I�u�W�F�N�g
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
					bool isHitShot = pShot->isCol(*pEnemy);    //�e���G�ɓ�����ƒe��������
					bool isHitEnemy = pEnemy->isCol(*pShot);   //�e���G�ɓ�����ƓG��������
					bool isHitPlayer = pPlayer->isCol(*pShot); //�e���v���C���[�ɓ�����ƃv���C���[��������
					bool isHitObject = pObject->isCol(*pShot); //�e���I�u�W�F�N�g�ɓ�����ƃI�u�W�F�N�g��������
					if (isHitShot) //isHit = true
					{
						pShot->shotDead();
					}
					if (isHitEnemy)
					{	
						pEnemy->enemyDead();

						//�G��S���|������N���A��ʂɍs��
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
						
						//�v���C���[�����񂾂玸�s��ʂɍs��
						return (new SceneFailResult);
					}
					if (isHitObject)
					{	
						//�I�u�W�F�N�g��10��e��������Ə�����
						m_hitObjectCount++;
						if (m_hitObjectCount >= 10)
						{
							pObject->objectDead();
							m_hitObjectCount = 0;
						}
						pObject->chageSize(); //�I�u�W�F�N�g�̃T�C�Y���������Ȃ�
						pShot->shotDead();    //�I�u�W�F�N�g�ɒe��������ƒe��������
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
	return this;
}

//�`��
void SceneMain::draw()
{
//	DrawString(m_textPosX, 0, "���C�����", GetColor(255, 255, 255));

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

	for (auto& pObject : m_pObjectVt)
	{
		assert(pObject);
		pObject->draw();
	}
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

//��ԉ��̓G�݂̂ɒe��ł�����
bool SceneMain::isCheckEnemyShot(Vec2 shotPos) //pos = �e�̔��ˈʒu
{
	for (auto& pEnemy : m_pEnemyVt)
	{
		if (shotPos.y > pEnemy->getBottom()) continue;      //�e����ɓG�������ꍇ�`�F�b�N���Ȃ�
		if (shotPos.x > pEnemy->getLeft())   continue;      //�e��荶�ɓG�������ꍇ�`�F�b�N���Ȃ�
		if (shotPos.x < pEnemy->getRight())  continue;      //�e���E�ɓG�������ꍇ�`�F�b�N���Ȃ�

		return false;
	}
	return true;
}
