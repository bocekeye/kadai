#include "DxLib.h"

#include "player.h"
#include "game.h"
#include  "SceneMain.h"

namespace
{
	constexpr float kSpeed = 0.1f;

	//プレイヤーのサイズ
	constexpr int kSize = 20;

	constexpr int kShotInterval = 16;
}


Player::Player()
{
	m_pMain = nullptr;
	m_shotInterval = 0;
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2; 
	m_pos.y = 400;
	m_vec.x = 0;
	m_vec.y = 0;
	m_shotInterval = 0;
}

void Player::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_2)
		{
			if (m_pMain->createShot(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}
	
	if (padState & PAD_INPUT_LEFT)
	{
		m_vec.x -= kSpeed;
	}
	if (padState & PAD_INPUT_RIGHT)
	{
		m_vec.x += kSpeed;
	}
	m_pos += m_vec;
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}
	if (m_pos.x > Game::kScreenWidth - kSize)
	{
		m_pos.x = Game::kScreenWidth - kSize;
	}
}

void Player::draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + kSize, m_pos.y + kSize, GetColor(255, 255, 255), true);
}