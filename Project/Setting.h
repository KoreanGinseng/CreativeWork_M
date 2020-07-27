#pragma once
#include "Common.h"
#include "Button.h"
#include "BackRender.h"

constexpr int ArrowOffsetX = (SceneWidth / 2) + 30;
constexpr int ArrowOffsetY =                    60;
constexpr int ArrowSize    =                    60;

class CSetting : public MyApp::CScene
{
private:

	CButton                 m_SelectLeft_1_1;
	CButton                 m_SelectLeft_1_2;
	CButton                 m_SelectRight_1_1;
	CButton                 m_SelectRight_1_2;
				            
	CButton                 m_SelectLeft_2_1;
	CButton                 m_SelectLeft_2_2;
	CButton                 m_SelectRight_2_1;
	CButton                 m_SelectRight_2_2;
				            
	CButton                 m_Back;
				            
	CBackRender             m_BackRender;

	std::shared_ptr<CFontA> m_pFont;

public:

	explicit CSetting(const InitData& init);

	virtual ~CSetting(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;

	static void Save(void);

	static bool Load(void);

	static KeyLength& GetKeyLength(void);

	static PianoKey& GetKeyOffset(void);

};

