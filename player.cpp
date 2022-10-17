#include  "DxLib.h"

#include  "player.h"
#include  "game.h"
#include  "SceneMain.h"

namespace
{
	constexpr float kSpeed = 0.1f;

	//�v���C���[�̃T�C�Y
	constexpr int kSize = 20;

	constexpr int kShotInterval = 16;
}


Player::Player()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
	m_isExist = false;
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2; 
	m_pos.y = 400;
	m_colSize.x = kSize;
	m_colSize.y = kSize;
	m_vec.x = 0;
	m_vec.y = 0;
	m_shotInterval = 0;

	m_isExist = true;
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
			if (m_pMain->playerShot(getPos()))
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
	//����ł���G�͕\�����Ȃ�
	if (!m_isExist) return;

	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
}

bool Player::isCol(Shot& shot)
{
	// ���݂��Ă��Ȃ��ꍇ
	if (!m_isExist)return false;
	if (!shot.isExist()) return false;

	//�������e�������ł͂Ȃ��ꍇ
	if (shot.getShotPlayer())
	{
		return false;
	}

	if (shot.getLeft() > getRight())return false;
	if (shot.getRight() < getLeft())return false;
	if (shot.getUp() > getBottom())return false;
	if (shot.getBottom() < getUp())return false;

	return true;
}

void Player::playerDead()
{
	m_isExist = false;
}