#include "DxLib.h"
#include "shot.h"
#include "game.h"
#include "Enemy.h"
namespace
{
	//�e�̑傫��
	constexpr int kSize = 10;

	//�v���C���[�̒e�̑��x
	constexpr float kShotPlayerSpeed = -8.0f;

	//�G�̒e�̑��x
	constexpr float kShotEnemySpeed = 5.0f;
}


Shot::Shot()
{
	m_handle = -1;
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_vec.y = 0.0f;

	m_pMain = nullptr;
	m_isPlayer = false;
	m_isExist = false;
}


void Shot::init()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_vec.y = 0.0f;

	m_colSize.x = kSize;
	m_colSize.y = kSize;
}

//�v���C���[�̒e
void Shot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	/*m_pos.x = m_colSize.x / 2;
	m_pos.y = m_colSize.y / 2;*/
	m_vec.y = kShotPlayerSpeed;
}

//�G�̒e
void Shot::enemyStart(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	/*m_pos.x = m_colSize.x / 2;
	m_pos.y = m_colSize.y / 2;*/
	m_vec.y = kShotEnemySpeed;
}

void Shot::update()
{
	if (!m_isExist) return;
	m_pos += m_vec;

	if (m_pos.y < 0.0f)
	{
		m_isExist = false;
	}
	if (m_pos.y > Game::kScreenHeight - m_colSize.y)
	{
		m_isExist = false;
	}
}
// �\��
void Shot::draw()
{
	if (!m_isExist) return;
//	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}


//�e�ƓG�Ƃ̓����蔻��
bool Shot::isCol(Enemy& enemy)
{
	//���݂��Ă��Ȃ��ꍇ
	if (!m_isExist)return false;
	if (!enemy.isExist()) return false;

	if (enemy.getLeft() > getRight())return false;
	if (enemy.getRight() < getLeft())return false;
	if (enemy.getUp() > getBottom())return false;
	if (enemy.getBottom() < getUp())return false;

	//���ł��Ȃ��悤�ɂ���
	if (!isGetShotPlayer())
	{
		return false;
	}


	return true;
}

void Shot::shotDead()
{
	m_isExist = false;
}

