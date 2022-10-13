#pragma once
#include "DxLib.h"
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~SceneTitle() {}

	virtual void init();
	virtual void end() {}

	virtual void update();
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:
	int m_textPosY;
	int m_textVecY;

	int m_isEnd;

};

