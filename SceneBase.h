#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}


	 void init() {}
	 void end() {}

	 virtual SceneBase* update() { return this; }
	 virtual void draw() {}

	// シーン終了
	virtual bool isEnd() { return false; }
};
