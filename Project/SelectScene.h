#pragma once
#include "Common.h"
#include "Button.h"
#include "BackRender.h"

class CSelectScene : public MyApp::CScene
{
private:

	CButton                      m_SelectBtnUp;
	CButton                      m_SelectBtnDown;
	CButton                      m_PlayBtn;
	CButton                      m_PlayAutoBtn;
	CButton                      m_SetBtn;
	CButton                      m_SelectBtnLeft_1;
	CButton                      m_SelectBtnLeft_2;
	CButton                      m_SelectBtnRight_1;
	CButton                      m_SelectBtnRight_2;
							     
	std::shared_ptr<CTexture>    m_pSelect1Texture;
	std::shared_ptr<CTexture>    m_pSelect2Texture;
							     
	std::shared_ptr<CFontA>      m_pNameFont;
	std::shared_ptr<CFontA>      m_pInfoFont;
							     
	int                          m_TruckIndex;

	CEaseMotionController<float> m_ArrowMotion;

	CBackRender                  m_BackRender;

public:

	explicit CSelectScene(const CSelectScene::InitData& init);

	virtual ~CSelectScene(void);

	virtual void Update(void) override;

	virtual void Render(void) override;

private:

	int LoopMusicNo(const int& offset) const;
};

