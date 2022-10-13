#include "DxLib.h"
#include "Enemy.h"

#include "game.h"
namespace
{
	constexpr int kSize = 20;
	constexpr float kSpeed = 2.0f;

	constexpr int kEnemyInterval = 10;
}


Enemy::Enemy()
{
	m_pMain = nullptr;
	m_enemyInterval = 0;
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

	m_enemyInterval = 0;
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
	m_enemyInterval--;
	if (m_enemyInterval < 0) m_enemyInterval = 0;

	if (m_enemyInterval <= 0)
	{
		
	}
	if (m_pos.x > Game::kScreenWidth - m_size.x)
	{
		m_pos.x = Game::kScreenWidth - m_size.x;
		m_pos.y += 20;
		m_vec.x *= -1;
	}
	if (m_pos.x < 0.0f)
	{
		m_pos.x = 0.0f;
		m_pos.y += 20;
		m_vec.x *= -1;
	}

	m_pos += m_vec;
}

void Enemy::draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GetColor(255, 255, 255), true);
}

