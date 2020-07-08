#include "MIDIOut.h"

CMIDIOut::CMIDIOut(void)
{
	if (midiOutOpen(&m_MidiOutHandle, MIDI_MAPPER, 0, 0, 0) != MMSYSERR_NOERROR)
	{
		MOF_PRINTLOG("midiOutOpenError");
		std::exit(0);
	}
	for (int i = 0; i < 16; i++)
	{
		ChangeInstrument(GMInstrument::AcosticGrandPiano, i);
	}
}

CMIDIOut::~CMIDIOut(void)
{
	midiOutReset(m_MidiOutHandle);
	midiOutClose(m_MidiOutHandle);
}

void CMIDIOut::Play(const float & volume, const MofU8 & keyCode, const MofU8& channel)
{
	Play(MofU8(127 * volume), keyCode, channel);
}

void CMIDIOut::Play(const MofU8 & velocity, const MofU8 & keyCode, const MofU8& channel)
{
	m_bPlay[channel][keyCode] = true;
	DWORD msg = 0x00000090;
	msg |= velocity << 16;
	msg |= keyCode  <<  8;
	msg |= channel  <<  0;
	midiOutShortMsg(m_MidiOutHandle, msg);
}

void CMIDIOut::Stop(const MofU8 & keyCode, const MofU8& channel)
{
	m_bPlay[channel][keyCode] = false;
	DWORD msg = 0x007F0080;
	msg |= keyCode << 8;
	msg |= channel << 0;
	midiOutShortMsg(m_MidiOutHandle, msg);
}

bool CMIDIOut::IsPlay(const MofU8 & keyCode, const MofU8& channel)
{
	return m_bPlay[channel][keyCode];
}

void CMIDIOut::ChangeInstrument(const GMInstrument & instrument, const MofU8& channel)
{
	m_Instrument = instrument;
	DWORD msg    = 0x000000C0;
	msg         |= m_Instrument << 8;
	msg         |= channel      << 0;
	midiOutShortMsg(m_MidiOutHandle, msg);
}

CMIDIOut& CMIDIOut::GetMIDIOut(void)
{
	static CMIDIOut midiOut;
	return midiOut;
}
