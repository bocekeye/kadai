#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}


	 void init() {}
	 void end() {}

	 void update() {}
	 void draw() {}

	// �V�[���I��
	virtual bool isEnd() { return false; }
};
