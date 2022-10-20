#pragma once

#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult()
	{
		m_textPosX = 0;
		m_textPosY = 0;
		m_textVecY = 0;
		m_resultTime = 0;
		m_isEnd = false;
	}
	virtual ~SceneResult() {}

	virtual void init();
	virtual void end() {}

	virtual SceneBase* update()  override;
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:
	int m_textPosX;
	int m_textPosY;
	int m_textVecY;

	int m_resultTime;

	int m_isEnd;

};

