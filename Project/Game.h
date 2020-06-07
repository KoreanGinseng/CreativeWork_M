#pragma once
#include "Common.h"
#include "Button.h"
#include "WindowUtillities.h"
#include "Player.h"

class CGame : public MyApp::CScene
{
private:

	std::shared_ptr<CFontA>  m_pBtnFont;

	CButton                  m_BtnWindowSize[WINDOWSIZE_CONT];

	CButton                  m_BtnAppForward;

	bool                     m_bForward;

	CButton                  m_BtnGoTitle;

	CPlayer                  m_Player;

public:
	
	explicit CGame(const CGame::InitData& init);

	virtual ~CGame(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) const override;

};