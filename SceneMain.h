#pragma once
#include "SceneBase.h"
#include "shot.h"
#include "player.h"
#include "Object.h"
#include <vector>

class Enemy;

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_hitEnemyCount = 0;
		m_hitObjectCount = 0;
		m_hitEnemyCount = 0;
		m_hitObjectCount = 0;
		m_hObjectGrahic = -1;

		m_hPlayerGraghic = -1;
		m_hEnemyGraghic = -1;
		m_hPlayerShotGraghic = -1;
		m_hEnemyShotGraghic = -1;
		m_hObjectGrahic = -1;

	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;

	virtual void draw();

	//�v���C���[�̃V���b�g�̐���
	bool playerShot(Vec2 pos);
	//�G�̃V���b�g�̐���
	bool enemyShot (Vec2 pos);

	//��ԉ��ɂ���G���e��łĂ邩�ǂ���
	bool isCheckEnemyShot(Vec2 pos);

//	virtual bool isEnd() { return m_isEnd; }
private:
	// �e�L�X�g�\���ʒu�ύX
	int m_textPosX;
	int m_textVecX;

	int m_hitEnemyCount; //�G�ɒe�������������̃J�E���g
	int m_hitObjectCount; //�I�u�W�F�N�g�ɒe�������������̃J�E���g

	//�v���C���[�O���t�B�b�N�n���h��
	int m_hPlayerGraghic;
	int m_hEnemyGraghic;
	int m_hPlayerShotGraghic;
	int m_hEnemyShotGraghic;
	int m_hObjectGrahic;

	//�v���C���[
	Player m_player;

	std::vector<Object*> m_pObjectVt;
	std::vector<Player*> m_pPlayerVt;
	std::vector<Shot*>   m_pShotVt;
	std::vector<Enemy*>  m_pEnemyVt;
};