#pragma once

#include "SceneBase.h"

class SceneFailResult : public SceneBase
{
public:
	SceneFailResult()
	{
		m_textPosX = 0;
		m_textPosY = 0;
		m_resultTime = 0;
		m_isEnd = false;
	}
	virtual ~SceneFailResult() {}

	virtual void init();
	virtual void end() {}

	virtual SceneBase* update()  override;
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:

	// テキスト表示位置変更
	int m_textPosX;  
	int m_textPosY;

	int m_resultTime;

	int m_isEnd;
};
