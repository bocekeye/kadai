#include "Object.h"
#include "DxLib.h"
#include "shot.h"
//#include

namespace
{
	//�I�u�W�F�N�g�T�C�Y
	constexpr int kSize = 50;
}

Object::Object()
{
	m_handle = -1;
	m_hitCount = 0;
	m_num = 0;
	m_pMain = nullptr;
	m_isExist = false;
}

void Object::init()
{
	m_pMain = nullptr;
	m_isExist = true;
	m_colSize.x = kSize;
	m_colSize.y = kSize;
	m_hitCount = 0;
	m_num = 0;
}
void Object::set(Vec2 pos)
{
	m_pos = pos;
}
void Object::update()
{
	if (!m_isExist) return;
}

void Object::draw()
{
	//����ł���G�͕\�����Ȃ�
	if (!m_isExist) return;

	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(0, 255, 255), false);
}

void Object::chageSize()
{
	//�I�u�W�F�N�g�ɓ����邲�ƂɃT�C�Y������������
	m_colSize *=  0.95;
}


bool Object::isCol(Shot& shot)
{
	//���݂��Ă��Ȃ��ꍇ
	if (!m_isExist)return false;
	if (!shot.isExist()) return false;

	if (shot.getLeft() > getRight()) return false;
	if (shot.getRight() < getLeft()) return false;
	if (shot.getUp() > getBottom())  return false;
	if (shot.getBottom() < getUp())  return false;

	return true;
}

void Object::objectDead()
{
	/*m_hitCount++;
	m_num += m_hitCount;
	if (m_num >= 5)
	{
		m_isExist = false;
		m_num = 0;
	}*/

	m_isExist = false;
}
