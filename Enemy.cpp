#include "DxLib.h"
#include "Enemy.h"
#include "SceneMain.h"
#include "game.h"
namespace
{
	//敵のサイズ
	constexpr int kSize = 20;

	//敵のスピード
	constexpr float kSpeed = 2.0f;

	//
	constexpr int kWaitFrame = 10;

	//敵のショット間隔
	constexpr int kEnemyShotInterval = 100;
}


Enemy::Enemy()
{
	m_pMain = nullptr;
	m_waitFrame = 0;
}
Enemy::~Enemy()
{

}

void Enemy::init()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_size.x = kSize;
	m_size.y = kSize;
	m_vec.x = kSpeed;
	m_vec.y = 0;

	m_waitFrame = 0;
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
	if (m_waitFrame < 0) m_waitFrame = 0;

	if (m_waitFrame <= 0)
	{
		
	}
	if (m_pos.x > Game::kScreenWidth - m_size.x)
	{
	//	m_pos.x = Game::kScreenWidth - m_size.x;
		m_pos.y += 20;
		m_vec.x *= -1;
	}
	if (m_pos.x < 0.0f)
	{
	//	m_pos.x = 0.0f;
		m_pos.y += 20;
		m_vec.x *= -1;
	}
	m_pos += m_vec;

	m_enemyShotInterval--;

	if (m_enemyShotInterval < 0) m_enemyShotInterval = 0;

	if (m_enemyShotInterval <= 0)
	{
		if (m_pMain->enemyShot(getPos()))
		{
			m_enemyShotInterval = kEnemyShotInterval;

		}
	}
}

void Enemy::draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GetColor(255, 255, 255), true);
}

void Enemy::addEnemyShot(Vec2 pos)
{
	m_pos = pos;

	

}
