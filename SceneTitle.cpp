#include "DxLib.h"
#include "game.h"

#include "SceneTitle.h"	
#include "SceneMain.h"

void SceneTitle::init()
{
	m_textPosX = 250;
	m_textPosY = 300;

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		return(new SceneMain);
		//m_isEnd = true;
	}

	return this;
}
void SceneTitle::draw()
{
	DrawString(m_textPosX + 20, m_textPosY, "�V���[�e�B���O�Q�[��", GetColor(255, 255, 255));
	DrawString(m_textPosX - 60, m_textPosY + 30, "�L�[�{�[�h��Z�܂���PAD��A�������ăQ�[���X�^�[�g", GetColor(255, 255, 255));
	DrawString(m_textPosX - 40, m_textPosY +80, "-----X�܂���A�Œe�𔭎˂ł��܂�-----", GetColor(255, 255, 255));
}