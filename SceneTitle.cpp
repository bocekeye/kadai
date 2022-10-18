#include "DxLib.h"
#include "SceneTitle.h"	


void SceneTitle::init()
{
	
	m_textPosX = 0;
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
}

void SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		m_isEnd = true;
	}
}
void SceneTitle::draw()
{
	DrawString(m_textPosX, m_textPosY, "タイトル画面", GetColor(255, 255, 255));
	DrawString(m_textPosX, m_textPosY + 15, "Zを押してゲームスタート", GetColor(255, 255, 255));
}