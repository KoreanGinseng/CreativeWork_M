#pragma once
#include "MIDIDefine.h"
#include <mmsystem.h> 

#pragma comment(lib, "winmm.lib")

class CMIDIOut
{
protected:

	HMIDIOUT          m_MidiOutHandle;

	bool              m_bPlay[256];

	GMInstrument      m_Instrument;

public:

	CMIDIOut(void);

	virtual ~CMIDIOut(void);

	void Play(const float& volume, const MofU8& keyCode);
	void Play(const MofU8& velocity, const MofU8& keyCode);

	void Stop(const MofU8& keyCode);

	bool IsPlay(const MofU8& keyCode);

	void ChangeInstrument(const GMInstrument& instrument);

	static CMIDIOut GetMIDIOut(void);
};

extern CMIDIOut g_Midiout;
