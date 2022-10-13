#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}


	 void init() {}
	 void end() {}

	 void update() {}
	 void draw() {}

	// シーン終了
	virtual bool isEnd() { return false; }
};
