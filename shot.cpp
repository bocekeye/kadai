#include "DxLib.h"
#include "shot.h"
#include "game.h"

namespace
{

	constexpr float kShotSpeed = -10.0f;

}


Shot::Shot()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_vec.y = 0.0f;
	m_pMain = nullptr;
	m_isExist = false;

}

Shot::~Shot()
{


}
void Shot::init()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_vec.y = 0.0f;
}


void Shot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;

	m_vec.y = kShotSpeed;
}

void Shot::update()
{
	m_pos += m_vec;
	if (!m_isExist) return;
}
// •\Ž¦
void Shot::draw()
{
	if (!m_isExist) return;
	DrawCircle(m_pos.x, m_pos.y, 10, GetColor(255,255,255), true);
}

bool Shot::isCol(Enemy& enemy)
{
	if (!m_isExist)return false;
	if (!enemy.isExist()) return false;


	if (enemy.getLeft() < getRight())return false;
	if (enemy.getRight() > )return false;
	if (enemy.getUp() < )return false;
	if (enemy.getBottom() > )return false;


}