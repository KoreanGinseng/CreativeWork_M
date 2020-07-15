#pragma once
#include "Common.h"
#include "Button.h"

class CTitle : public MyApp::CScene
{
private:
			                  
	float                        m_Scale;
			                     
	float                        m_Rotate;
							     
	std::shared_ptr<CTexture>    m_pTitleTexture;

	CEaseMotionController<float> m_ScaleMotion;

public:
	
	explicit CTitle(const CTitle::InitData& init);

	virtual ~CTitle(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) const override;

};