#pragma once
#include "MIDIDefine.h"
#include <mmsystem.h> 

#pragma comment(lib, "winmm.lib")

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT msg, DWORD dwInstance, DWORD wpar1, DWORD lpar2);

class CMIDIInput
{
public:

	struct InputData {
		bool          bPush      = false;
		bool          bHold      = false;
		bool          bPull      = false;
		unsigned char velocity   = 0x00;
		bool          bPushCheck = false;
		bool          bPullCheck = false;
	};

protected:

	LPHMIDIIN              m_pMIDIDeviceHandle;

	InputData              m_Input[256];

	bool Create(void);

	void Release(void);

public:
	
	CMIDIInput(void);

	virtual ~CMIDIInput(void);

	static CMIDIInput& GetMIDIManager(void);

	void Refresh(unsigned char note, unsigned char velocity, bool bPush, bool bHold, bool bPull);

	void RefreshKey(void);

	UINT GetDeviceCount(void) const;

	HMIDIIN GetDeviceHandle(const int& no) const;

	MMRESULT GetMMResult(UINT devNo, LPMIDIINCAPS pCap) const;

	MMRESULT GetMMResult(UINT devNo) const;

	CString GetDeviceName(UINT devNo) const;

	bool IsKeyPush(MofU8 key) const;

	bool IsKeyHold(MofU8 key) const;
	
	bool IsKeyPull(MofU8 key) const;

	unsigned char GetVelocity(MofU8 key) const;

	static bool IsBlackKey(MofU8 key);

	static bool IsWhiteKey(MofU8 key);
};

#define g_MIDIInput  CMIDIInput::GetMIDIManager()