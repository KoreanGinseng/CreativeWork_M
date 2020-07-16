#pragma once
#include "MIDIDefine.h"
#include <mmsystem.h> 

#pragma comment(lib, "winmm.lib")

class CMIDIOut
{
protected:

	HMIDIOUT          m_MidiOutHandle;

	bool              m_bPlay[16][256];

	GMInstrument      m_Instrument;

public:

	CMIDIOut(void);

	virtual ~CMIDIOut(void);

	void Play(const float& volume, const MofU8& keyCode, const MofU8& channel);
	void Play(const MofU8& velocity, const MofU8& keyCode, const MofU8& channel);

	void Stop(const MofU8& keyCode, const MofU8& channel);

	bool IsPlay(const MofU8& keyCode, const MofU8& channel);

	void ChangeInstrument(const GMInstrument& instrument, const MofU8& channel);

	static CMIDIOut& GetMIDIOut(void);
};

extern CMIDIOut g_MidiOutput;
