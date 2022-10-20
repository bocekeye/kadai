#include "DxLib.h"
#include "shot.h"
#include "game.h"
#include "Enemy.h"
namespace
{
	constexpr int kSize = 10;
	constexpr float kShotSpeed = -8.0f;
}


Shot::Shot()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_vec.y = 0.0f;
	m_pMain = nullptr;
	m_isPlayer = false;
	m_isExist = false;

}

Shot::~Shot()
{

}
void Shot::init()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_colSize.x = kSize;
	m_colSize.y = kSize;
	m_vec.y = 0.0f;
}

//ÉvÉåÉCÉÑÅ[ÇÃíe
void Shot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	/*m_pos.x = m_colSize.x / 2;
	m_pos.y = m_colSize.y / 2;*/
	m_vec.y = kShotSpeed;
}

//ìGÇÃíe
void Shot::enemyStart(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	/*m_pos.x = m_colSize.x / 2;
	m_pos.y = m_colSize.y / 2;*/
	m_vec.y = -kShotSpeed;
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
// ï\é¶
void Shot::draw()
{
	if (!m_isExist) return;
	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
}


//íeÇ∆ìGÇ∆ÇÃìñÇΩÇËîªíË
bool Shot::isCol(Enemy& enemy)
{
	//ë∂ç›ÇµÇƒÇ¢Ç»Ç¢èÍçá
	if (!m_isExist)return false;
	if (!enemy.isExist()) return false;

	if (enemy.getLeft() > getRight())return false;
	if (enemy.getRight() < getLeft())return false;
	if (enemy.getUp() > getBottom())return false;
	if (enemy.getBottom() < getUp())return false;

	//é©ñ≈ÇµÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈ
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

