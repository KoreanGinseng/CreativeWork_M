#pragma once
#include "Common.h"
#include "MIDIInput.h"
#include "MIDIOut.h"
#include "Note.h"

class CGame : public MyApp::CScene
{
private:

	CStopWatch        m_StartTime;

	float             m_EndTime;

public:
	
	explicit CGame(const CGame::InitData& init);

	virtual ~CGame(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) const override;

	void RenderKeyLine(void) const;

	void RenderCheckLine(void) const;

	static void RenderWhiteKey(const PianoKey& offset, const KeyLength& length);

	static void RenderBlackKey(void);

};