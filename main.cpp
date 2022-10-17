#include "DxLib.h"
#include "SceneManeger.h"
#include "game.h"
#include "player.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	//�E�B���h�E���[�h���ݒ�
	SetMainWindowText(Game::kTitkeText);
	//��ʂ̃T�C�Y
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepht);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			    // �G���[���N�����璼���ɏI��
	}
	
	//�_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[���̏�����
	SceneManager scene;
	scene.init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		//��ʂ̕\��
		ClearDrawScreen();

		scene.update();
		scene.draw();



		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		//esc�L�[����������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		while (GetNowHiPerformanceCount() - time < 1667)
		{

		}

	}
	
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				    // �\�t�g�̏I�� 
}
