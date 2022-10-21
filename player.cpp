#include  "DxLib.h"

#include  "player.h"
#include  "game.h"
#include  "SceneMain.h"

namespace
{
	//プレイヤーの左右移動速度
	constexpr float kSpeed = 4.0f;

	//プレイヤーのサイズ
	constexpr int kSize = 25.0f;

	//ショット間隔
	constexpr int kShotInterval = 30;
}


Player::Player()
{
	m_handle = -1;
	m_shotInterval = 0;

	m_pMain = nullptr;
	m_isExist = false;
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2; 
	m_pos.y = Game::kScreenHeight - 100.0f;
	m_colSize.x = kSize;
	m_colSize.y = kSize;
	//m_vec.x = kSpeed;

	m_shotInterval = 0;

	m_isExist = true;
}

void Player::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;


	//存在している間だけ弾を出す
	if (m_isExist)
	{
		if (m_shotInterval <= 0)
		{
			if (padState & PAD_INPUT_2)
			{
				if (m_pMain->playerShot(getPos()))
				{
					m_shotInterval = kShotInterval;
				}
			}
		}
	}
	
	if (padState & PAD_INPUT_LEFT)
	{
		m_pos.x -= kSpeed;
	}
	if (padState & PAD_INPUT_RIGHT)
	{
		m_pos.x += kSpeed;
	}
		m_pos += m_vec;

	//プレイヤーの移動制限
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}
	if (m_pos.x > Game::kScreenWidth - m_colSize.x)
	{
		m_pos.x = Game::kScreenWidth - m_colSize.x;
	}
}

void Player::draw()
{
	//死んでいる敵は表示しない
	if (!m_isExist) return;

//	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
//	DrawLine(0, Game::kScreenHeight - 1, Game::kScreenWidth, Game::kScreenHeight - 1, GetColor(255, 255, 255));
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}


//弾の当たり判定
bool Player::isCol(Shot& shot)
{
	// 存在していない場合
	if (!m_isExist)return false;
	if (!shot.isExist()) return false;

	//撃った弾が自分だった場合当たり判定は行わない
	if (shot.isGetShotPlayer()) return false;

	if (shot.getLeft() > getRight()) return false;
	if (shot.getRight() < getLeft()) return false;
	if (shot.getUp() > getBottom())  return false;
	if (shot.getBottom() < getUp())  return false;

	return true;
}

void Player::playerDead()
{
	m_isExist = false;
}