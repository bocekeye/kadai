#include "DxLib.h"
#include "Enemy.h"
#include "SceneMain.h"
#include "game.h"
namespace
{
	//敵のサイズ
	constexpr int kSize = 30;

	//敵のスピード
	constexpr float kSpeed = 6.0f;

	//移動するまでの時間
	constexpr int kWaitFrame = 80;

	//敵のショット間隔
	constexpr int kEnemyShotInterval = 200;
}


Enemy::Enemy()
{
	m_handle = -1;
	m_waitFrame = 0;
	m_enemyShotInterval = 0;
	m_slide = 0;
	m_moveCount = 0;

	m_pMain = nullptr;
	m_isExist = false;
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
		if (m_slide > 0)  //右方向の移動
		{
			m_pos.x += kSpeed;
			if (m_moveCount >= 0)
			{
				m_pos.y += 20.0f;
				m_slide = -1;
			}
		}
		if (m_slide < 0) //左方向の移動
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
	
	//存在している場合のみ弾を出す
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

	if (m_pos.y >= Game::kScreenHeight - 100.0f)
	{
		
	}
}

void Enemy::draw()
{
	//死んでいる敵は表示しない
	if (!m_isExist) return;

//	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(0, 255, 255), true);
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

//敵と弾の当たり判定
bool Enemy::isCol(Shot& shot)
{
	//存在していない場合
	if (!m_isExist)return false;
	if (!shot.isExist()) return false;

	//弾を打ったのが敵の場合当たり判定をなしにする
	if (!shot.isGetShotPlayer()) return false;
		
	if (shot.getLeft() > getRight()) return false;
	if (shot.getRight() < getLeft()) return false;
	if (shot.getUp() > getBottom())  return false;
	if (shot.getBottom() < getUp())  return false;

	return true;
}

//プレイヤーより敵の座標が大きくなったらゲームを終了させるため
bool Enemy::isCompare(Player& player)
{
	if (player.getLeft() > getRight()) return false;
	if (player.getRight() < getLeft()) return false;
	if (player.getUp() > getBottom())  return false;
	if (player.getBottom() < getUp())  return false;

	return true;
}

void Enemy::enemyDead()
{
	m_isExist = false;
}
