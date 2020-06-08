#include "MIDIInput.h"

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT msg, DWORD dwInstance, DWORD wpar1, DWORD lpar2)
{
	switch (msg)
	{
	case MIM_OPEN:
		MOF_PRINTLOG("MIDI device was opened\n");
		break;

	case MIM_CLOSE:
		MOF_PRINTLOG("MIDI device was closed\n");
		break;

	case MIM_DATA:
	{
		//MOF_PRINTLOG("MIM_DATA: msg=%08X, p1=%08X, p2=%08X\n", msg, wpar1, lpar2);
		
		unsigned char status_byte  = (wpar1 & 0x000000f0);
		
		unsigned char data1        = (wpar1 & 0x0000ff00) >>  8;
		unsigned char data2        = (wpar1 & 0x00ff0000) >> 16;

		switch (status_byte)
		{
		case Event::MIDI_Note_Off:                // ノートオフ                     (data1 :          ノート番号, data2 :      オフベロシティ)
		{
			g_MIDIInput.Refresh(data1, 0, false, false, true);
			//MOF_PRINTLOG("ノート番号 = %u, オフベロシティ値 = %u\n", data1, data2);
			break;
		}

		case Event::MIDI_Note_On:                 //　ノートオン                    (data1 :          ノート番号, data2 :          ベロシティ)
		{
			g_MIDIInput.Refresh(data1, data2, true, true, false);
			//MOF_PRINTLOG("ノート番号 = %u, ベロシティ = %u\n", data1, data2);
			break;
		}

		case Event::MIDI_PolyPhonic_Key_Pressure: // ポリフォニックキープレッシャー (data1 :          ノート番号, data2 :      プレッシャー値)
		{
			//MOF_PRINTLOG("ノート番号 = %u, プレッシャー値 = %u\n", data1, data2);
			break;
		}

		case Event::MIDI_Control:                 // コントロールチェンジ           (data1 :    コントロール番号, data2 :      コントロール値)
		{
			// モードメッセージ
			switch (data1)
			{
			case 0x78: // オールサウンドオフ         (data2 :         ダミー)
				MOF_PRINTLOG("オールサウンドオフ\n");
				break;
			case 0x79: // リセットオールコントローラ (data2 :         ダミー)
				MOF_PRINTLOG("リセットオールコントローラ\n");
				break;
			case 0x7A: // ローカルコントローラ       (data2 : オフまたはオン)
				MOF_PRINTLOG("モノモードオン チャンネル数 = %u\n", data2);
				break;
			case 0x7B: // オールノートオフ           (data2 :         ダミー)
				MOF_PRINTLOG("オールノートオフ\n");
				break;
			case 0x7C: // オムニオフ                 (data2 :         ダミー)
				MOF_PRINTLOG("オムニオフ\n");
				break;
			case 0x7D: // オムニオン                 (data2 :         ダミー)
				MOF_PRINTLOG("オムニオン\n");
				break;
			case 0x7E: // モノモードオン             (data2 :   チャンネル数)
				MOF_PRINTLOG("モノモードオン チャンネル数 = %u\n", data2);
				break;
			case 0x7F: // ポリモードオン             (data2 :         ダミー)
				MOF_PRINTLOG("ポリモードオン\n");
				break;
			}
			MOF_PRINTLOG("コントロール番号 = %u, コントロール値 = %u\n", data1, data2);
			break;
		}

		case Event::MIDI_Program_Change:          // プログラムチェンジ             (data1 :      プログラム番号, data2 :                  - )
		{
			MOF_PRINTLOG("プログラム番号 = %u\n", data1);
			break;
		}

		case Event::MIDI_Channel_Pressure:        // チャンネルプレッシャー         (data1 :      プレッシャー値, data2 :                  - )
		{
			MOF_PRINTLOG("プレッシャー値 = %u\n", data1);
			break;
		}

		case Event::MIDI_Pitch_Bend:              // ピッチベンドチェンジ           (data1 : ピッチベンド値(LSB), data2 : ピッチベンド値(MSB))
		{
			MOF_PRINTLOG("LSB = %u, MSB = %u\n", data1, data2);
			break;
		}
		}

		//MOF_PRINTLOG("handle = %08X\n", hMidiIn);
		break;
	}
	break;

	case MIM_LONGDATA:
	case MIM_ERROR:
	case MIM_LONGERROR:
	case MIM_MOREDATA:
	default:
		break;
	}

	return;
}

bool CMIDIInput::Create(void)
{
	// 接続されているMIDI入力装置数を取得する。
	int cnt = GetDeviceCount();

	// 入力装置の数だけハンドルを作成する。
	m_pMIDIDeviceHandle = new HMIDIIN[cnt];

	// すべての入力装置を使えるように登録する。
	for (int i = 0; i < cnt; i++)
	{
		MMRESULT res =
		midiInOpen(&m_pMIDIDeviceHandle[i], i, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);

		// 開いたときエラーがあればエラーメッセージを出力するようにする。
		if (res != MMSYSERR_NOERROR)
		{
			char errmsg[MAXERRORLENGTH];
			MOF_PRINTLOG("Cannot open MIDI input device (ID=%u): ", i);
			midiInGetErrorText(res, errmsg, sizeof(errmsg));
			MOF_PRINTLOG("%s\n", errmsg);
			return false;
		}
	}

	// 使用可能な状態なら入力を受け付けるようにする。
	for (int i = 0; i < cnt; i++)
	{
		midiInStart(m_pMIDIDeviceHandle[i]);
		MOF_PRINTLOG("%08X\n", m_pMIDIDeviceHandle[i]);
	}

	return true;
}

void CMIDIInput::Release(void)
{
	// 接続されているMIDI入力装置数を取得する。
	int cnt = GetDeviceCount();

	// 接続数だけMIDI入力を止める。
	for (int i = 0; i < cnt; i++)
	{
		midiInStop(m_pMIDIDeviceHandle[i]);
		midiInReset(m_pMIDIDeviceHandle[i]);
		midiInClose(m_pMIDIDeviceHandle[i]);
	}

	// ハンドルの後始末。
	if (cnt == 1)
	{
		MOF_SAFE_DELETE(m_pMIDIDeviceHandle);
	}
	else
	{
		MOF_SAFE_DELETE_ARRAY(m_pMIDIDeviceHandle);
	}
}

void CMIDIInput::Refresh(unsigned char note, unsigned char velocity, bool bPush, bool bHold, bool bPull)
{
	m_Input[note].bPush      = bPush;
	m_Input[note].bHold      = bHold;
	m_Input[note].bPull      = bPull;
	m_Input[note].velocity   = velocity;
	m_Input[note].bPushCheck = false;
	m_Input[note].bPullCheck = false;
}

CMIDIInput::CMIDIInput(void)
{
	Create();
}

CMIDIInput::~CMIDIInput(void)
{
	Release();
}

CMIDIInput & CMIDIInput::GetMIDIManager(void)
{
	static CMIDIInput Proc;
	return Proc;
}

void CMIDIInput::RefreshKey(void)
{
	for (int i = 0; i < 256; i++)
	{
		if (m_Input[i].bPushCheck)
		{
			m_Input[i].bPush = false;
			continue;
		}
		if (m_Input[i].bPullCheck)
		{
			m_Input[i].bPull = false;
			continue;
		}
		if (m_Input[i].bPush)
		{
			m_Input[i].bPushCheck = true;
			continue;
		}
		if (m_Input[i].bPull)
		{
			m_Input[i].bPullCheck = true;
			continue;
		}
	}
}

UINT CMIDIInput::GetDeviceCount(void) const
{
	return midiInGetNumDevs();
}

HMIDIIN CMIDIInput::GetDeviceHandle(const int & no) const
{
	return m_pMIDIDeviceHandle[no];
}

MMRESULT CMIDIInput::GetMMResult(UINT devNo, LPMIDIINCAPS pCap) const
{
	return midiInGetDevCaps(devNo, pCap, sizeof(*pCap));
}

MMRESULT CMIDIInput::GetMMResult(UINT devNo) const
{
	MIDIINCAPS inCaps;
	return GetMMResult(devNo, &inCaps);
}

CString CMIDIInput::GetDeviceName(UINT devNo) const
{
	MIDIINCAPS inCaps;
	MMRESULT   res;

	// デバイスの情報を inCaps に格納
	res = GetMMResult(devNo, &inCaps);
	CString str = inCaps.szPname;

	return str;
}

bool CMIDIInput::IsKeyPush(MofU8 key) const
{
	return m_Input[key].bPush;
}

bool CMIDIInput::IsKeyHold(MofU8 key) const
{
	return m_Input[key].bHold;
}

bool CMIDIInput::IsKeyPull(MofU8 key) const
{
	return m_Input[key].bPull;
}

unsigned char CMIDIInput::GetVelocity(MofU8 key) const
{
	return m_Input[key].velocity;
}

bool CMIDIInput::IsBlackKey(MofU8 key)
{
	bool re =
		(key == PianoKey::C_S) ||
		(key == PianoKey::D_S) ||
		(key == PianoKey::F_S) ||
		(key == PianoKey::G_S) ||
		(key == PianoKey::A_S) ||
		(key == PianoKey::C0_S) ||
		(key == PianoKey::D0_S) ||
		(key == PianoKey::F0_S) ||
		(key == PianoKey::G0_S) ||
		(key == PianoKey::A0_S) ||
		(key == PianoKey::C1_S) ||
		(key == PianoKey::D1_S) ||
		(key == PianoKey::F1_S) ||
		(key == PianoKey::G1_S) ||
		(key == PianoKey::A1_S) ||
		(key == PianoKey::C2_S) ||
		(key == PianoKey::D2_S) ||
		(key == PianoKey::F2_S) ||
		(key == PianoKey::G2_S) ||
		(key == PianoKey::A2_S) ||
		(key == PianoKey::C3_S) ||
		(key == PianoKey::D3_S) ||
		(key == PianoKey::F3_S) ||
		(key == PianoKey::G3_S) ||
		(key == PianoKey::A3_S) ||
		(key == PianoKey::C4_S) ||
		(key == PianoKey::D4_S) ||
		(key == PianoKey::F4_S) ||
		(key == PianoKey::G4_S) ||
		(key == PianoKey::A4_S) ||
		(key == PianoKey::C5_S) ||
		(key == PianoKey::D5_S) ||
		(key == PianoKey::F5_S) ||
		(key == PianoKey::G5_S) ||
		(key == PianoKey::A5_S) ||
		(key == PianoKey::C6_S) ||
		(key == PianoKey::D6_S) ||
		(key == PianoKey::F6_S) ||
		(key == PianoKey::G6_S) ||
		(key == PianoKey::A6_S) ||
		(key == PianoKey::C7_S) ||
		(key == PianoKey::D7_S) ||
		(key == PianoKey::F7_S) ||
		(key == PianoKey::G7_S) ||
		(key == PianoKey::A7_S) ||
		(key == PianoKey::C8_S) ||
		(key == PianoKey::D8_S) ||
		(key == PianoKey::F8_S) ||
		(key == PianoKey::G8_S) ||
		(key == PianoKey::A8_S) ||
		(key == PianoKey::C9_S) ||
		(key == PianoKey::D9_S) ||
		(key == PianoKey::F9_S) ||
		(key == PianoKey::G9_S) ||
		(key == PianoKey::A9_S) ||
		(key == PianoKey::C10_S) ||
		(key == PianoKey::D10_S) ||
		(key == PianoKey::F10_S) ||
		(key == PianoKey::G10_S) ||
		(key == PianoKey::A10_S) ||
		(key == PianoKey::C11_S) ||
		(key == PianoKey::D11_S) ||
		(key == PianoKey::F11_S) ||
		(key == PianoKey::G11_S) ||
		(key == PianoKey::A11_S) ||
		(key == PianoKey::C12_S) ||
		(key == PianoKey::D12_S) ||
		(key == PianoKey::F12_S) ||
		(key == PianoKey::G12_S) ||
		(key == PianoKey::A12_S) ||
		(key == PianoKey::C13_S) ||
		(key == PianoKey::D13_S) ||
		(key == PianoKey::F13_S) ||
		(key == PianoKey::G13_S) ||
		(key == PianoKey::A13_S) ||
		(key == PianoKey::C14_S) ||
		(key == PianoKey::D14_S) ||
		(key == PianoKey::F14_S) ||
		(key == PianoKey::G14_S) ||
		(key == PianoKey::A14_S) ||
		(key == PianoKey::C15_S) ||
		(key == PianoKey::D15_S) ||
		(key == PianoKey::F15_S) ||
		(key == PianoKey::G15_S) ||
		(key == PianoKey::A15_S) ||
		(key == PianoKey::C16_S) ||
		(key == PianoKey::D16_S) ||
		(key == PianoKey::F16_S) ||
		(key == PianoKey::G16_S) ||
		(key == PianoKey::A16_S) ||
		(key == PianoKey::C17_S) ||
		(key == PianoKey::D17_S) ||
		(key == PianoKey::F17_S) ||
		(key == PianoKey::G17_S) ||
		(key == PianoKey::A17_S) ||
		(key == PianoKey::C18_S) ||
		(key == PianoKey::D18_S) ||
		(key == PianoKey::F18_S) ||
		(key == PianoKey::G18_S) ||
		(key == PianoKey::A18_S) ||
		(key == PianoKey::C19_S) ||
		(key == PianoKey::D19_S) ||
		(key == PianoKey::F19_S) ||
		(key == PianoKey::G19_S) ||
		(key == PianoKey::A19_S) ||
		(key == PianoKey::C20_S) ||
		(key == PianoKey::D20_S);

	return re;
}

bool CMIDIInput::IsWhiteKey(MofU8 key)
{
	return !IsBlackKey(key);
}
