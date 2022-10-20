#include "DxLib.h"
#include "Enemy.h"
#include "SceneMain.h"
#include "game.h"
namespace
{
	//�G�̃T�C�Y
	constexpr int kSize = 30;

	//�G�̃X�s�[�h
	constexpr float kSpeed = 7.0f;

	//�ړ�����܂ł̎���
	constexpr int kWaitFrame = 80;

	//�G�̃V���b�g�Ԋu
	constexpr int kEnemyShotInterval = 180;
}


Enemy::Enemy()
{
	m_pMain = nullptr;
	m_waitFrame = 0;
	m_enemyShotInterval = 0;
	m_isExist = false;
	m_slide = 0;
	m_moveCount = 0;
}
Enemy::~Enemy()
{

}

void Enemy::init()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_colSize.x = kSize;
	m_colSize.y = kSize;
	m_vec.x = kSpeed;
	m_vec.y = 0;
	m_isExist = true;
	m_enemyShotInterval = kEnemyShotInterval;
	m_waitFrame = 0;
	m_slide = -1;
	m_moveCount = 0;
}

void Enemy::set(Vec2 pos)
{
	m_pos = pos;
}
void Enemy::end()
{

}
void Enemy::update()
{
	m_waitFrame--;
	if (m_waitFrame <= 0)
	{
		m_moveCount += m_slide;
		if (m_slide > 0)  //
		{
			m_pos.x += kSpeed;
			if (m_moveCount >= 0)
			{
				m_pos.y += 20.0f;
				m_slide = -1;
			}
		}
		if (m_slide < 0)
		{
			m_pos.x -= kSpeed;
			if (m_moveCount <= -10)
			{
				m_pos.y += 20.0f;
				m_slide = 1;
			}
		}
		m_waitFrame = kWaitFrame;
	}

	m_enemyShotInterval--;

	if (m_enemyShotInterval < 0) m_enemyShotInterval = 0;
	
	//���݂��Ă���ꍇ�̂ݒe���o��
	if (m_isExist)
	{
		if (m_enemyShotInterval <= 0)
		{
			if (m_pMain->isCheckEnemyShot(getPos()))
			{
				if (m_pMain->enemyShot(getPos()))
				{
					m_enemyShotInterval = kEnemyShotInterval;
				}
			}
		}
	}
}

void Enemy::draw()
{
	//����ł���G�͕\�����Ȃ�
	if (!m_isExist) return;

	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(0, 255, 255), true);
}

//�G�ƒe�̓����蔻��
bool Enemy::isCol(Shot& shot)
{
	//���݂��Ă��Ȃ��ꍇ
	if (!m_isExist)return false;
	if (!shot.isExist()) return false;

	//�e��ł����̂��G�̏ꍇ�����蔻����Ȃ��ɂ���
	if (!shot.isGetShotPlayer()) return false;
		
	if (shot.getLeft() > getRight()) return false;
	if (shot.getRight() < getLeft()) return false;
	if (shot.getUp() > getBottom())  return false;
	if (shot.getBottom() < getUp())  return false;

	return true;
}
void Enemy::enemyDead()
{
	m_isExist = false;
}
