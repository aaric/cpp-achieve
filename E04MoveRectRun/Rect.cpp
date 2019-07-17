#include "stdafx.h"
#include "Rect.h"

const float Rect::c_fLength = 4.5f;
const float Rect::c_fWidth = 1.8f;

Rect::Rect()
{
}

Rect::~Rect()
{
}

// 获取当前位置(单位:米)
FLOAT2 Rect::GetPos()
{
	FLOAT2 pos(m_fx, m_fy);
	return pos;
}

// 移动位置,返回新位置坐标(单位:米)
FLOAT2 Rect::move(float fDeltaX, float fDeltaY)
{
	m_fx += fDeltaX;
	m_fy += fDeltaY;
	return GetPos();
}
