#include "game.h"
#include "DxLib.h"

#include "SceneFailResult.h"
#include "SceneTitle.h"

namespace
{
	constexpr int kResultTime = 200;
}

void SceneFailResult::init()
{
	m_textPosX = Game::kScreenWidth / 2 - 40;
	m_textPosY = Game::kScreenHeight / 2;
	m_resultTime = kResultTime;
	m_isEnd = false;
}

SceneBase* SceneFailResult::update()
{
	//一定時間経過したら、タイトルに戻る
	m_resultTime--;
	if (m_resultTime <= 0)
	{
		m_resultTime = kResultTime;
		return (new SceneTitle);
	}

	return this;
}

void SceneFailResult::draw()
{
	DrawString(m_textPosX, m_textPosY, "GAME OVER", GetColor(255, 255, 255));
}