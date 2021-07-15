#pragma once
#include "Common.h"

class CGame : public MyApp::CScene
{
private:

	CStopWatch                   m_StartTime;
					             
	float                        m_EndTime;
					             
	CScore                       m_Score;
							     
	ScoreKey                     m_ScoreKey;
							     
	std::shared_ptr<CFontA>      m_pFont;

	CEaseMotionController<float> m_ComboMotion;

	static MofU8                 m_sPlayChannel;

public:
	
	explicit CGame(const CGame::InitData& init);

	virtual ~CGame(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) override;

	void RenderKeyLine(void) const;

	void RenderCheckLine(void) const;

	static void RenderWhiteKey(const PianoKey& offset, const KeyLength& length);

	static void RenderBlackKey(void);
};