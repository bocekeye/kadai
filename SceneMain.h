#pragma once
#include "SceneBase.h"
#include "shot.h"
#include "player.h"

#include <vector>

class Enemy;

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_textPosX = 0;
		m_textVecX = 0;
		m_isEnd = false;
	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end() {}

	virtual void update();
	virtual void draw();

	//�v���C���[�̃V���b�g�̐���
	bool createShot(Vec2 pos);

	//�G�̃V���b�g�̐���
	bool enemyShot (Vec2 pos);

	virtual bool isEnd() { return m_isEnd; }
private:
	// �e�L�X�g�\���ʒu�ύX
	int m_textPosX;
	int m_textVecX;

	bool m_isEnd;


	//�v���C���[
	Player m_player;

	Shot m_shot;

	std::vector<Shot*> m_pShotVt;
	std::vector<Enemy*> m_pEnemyVt;
};