#pragma once

#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_textPosX = 0;
		m_textPosY = 0;
		m_isEnd = false;
	}
	virtual ~SceneTitle() {}

	virtual void init();
	virtual void end() {}

	virtual SceneBase* update() override;
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:
	int m_textPosX;
	int m_textPosY;

	int m_isEnd;

};

