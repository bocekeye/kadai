#include "DxLib.h"
#include "SceneTitle.h"	


void SceneTitle::init()
{
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
	DrawString(0, 0, "タイトル画面", GetColor(255, 255, 255));
	DrawString(0, 15, "Zを押してゲームスタート", GetColor(255, 255, 255));
}