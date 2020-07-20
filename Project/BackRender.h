#pragma once
#include "Common.h"

class CBackRender
{
private:

	float                        m_Scale;

	float                        m_Rotate;

	std::shared_ptr<CTexture>    m_pTitleTexture;

	CEaseMotionController<float> m_ScaleMotion;

	float                        m_BackIconRotate[30];

	Vector2                      m_BackIconPos[30];

	std::shared_ptr<CTexture>    m_pBackIconTexture[30];

public:
	
	CBackRender(void);
	
	~CBackRender(void);

	void Update(void);

	void Render(void) const;
};

