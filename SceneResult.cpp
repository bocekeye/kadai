#include "game.h"
#include "DxLib.h"

#include "SceneResult.h"
#include "SceneTitle.h"

namespace
{
	constexpr int kResultTime = 200;
}

void SceneResult::init()
{
	m_textPosX = Game::kScreenWidth / 2 - 30;
	m_textPosY = Game::kScreenHeight / 2;
	m_resultTime = kResultTime;
	m_isEnd = false;
}

SceneBase* SceneResult::update()
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

void SceneResult::draw()
{
	DrawString(m_textPosX, m_textPosY, "GAME Clear", GetColor(255, 255, 255));
}