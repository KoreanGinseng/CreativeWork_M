#include "Note.h"
#include "Common.h"
#include "MIDIInput.h"

// �Q�l�T�C�g
// http://torasukenote.blog120.fc2.com/blog-entry-104.html
// https://qiita.com/owts/items/8d641e8a8a423566db71#standard-midi-file-%E3%81%A8%E3%81%AF
// https://sites.google.com/site/yyagisite/material/smfspec
// http://maruyama.breadfish.jp/tech/smf/

NoteHitResult sip::CNote::m_sHitResult = NoteHitResult::NONE;
KeyLength     sip::CNote::m_sKeyLength = KeyLength::_88;
PianoKey      sip::CNote::m_sKeyOffset = PianoKey::A0;
Auto          sip::CNote::m_sAutoParam = Auto::Semi;

CDynamicArray<sip::CNoteArray>     g_NoteArray;
PlayResult                         g_PlayResult;

namespace sip
{
	CNote::CNote(void) :
		m_bStart(false),
		m_bShow(false),
		m_bBlack(false),
		m_bPlayTrack(false),
		m_pScore(nullptr)
	{
	}

	CNote::CNote(const InitState & state) :
		CNote()
	{
		Initialize(state);
	}

	CNote::~CNote(void)
	{

	}

	void CNote::Initialize(const InitState & state)
	{
		// �f�[�^�̃R�s�[�B
		m_NoteOnData  = state.noteOnData;
		m_NoteOffData = state.noteOffData;

		// �������������ŉ����A�F�A�ʒu���ς���B
		int offsetX = 0;
		int width = PianoWhiteKeyWidth;
		m_bBlack = false;
		if (CMIDIInput::IsBlackKey(m_NoteOnData.laneIndex))
		{
			m_bBlack = true;
			width = PianoBlackKeyWidth;

			// �����̏ꍇ�̂��炷�����B
			if (m_NoteOnData.laneIndex == PianoKey::A0_S)
			{
				offsetX = PianoWhiteKeyWidth - PianoBlackKeyWidth * 0.5f;
			}
			else
			{
				// �����̐������J�E���g����B
				int x = -1;
				for (int i = PianoKey::A0; i < m_NoteOnData.laneIndex; i++)
				{
					if (CMIDIInput::IsWhiteKey(i))
					{
						continue;
					}
					x++;
				}
				// �Ƃ肠�������炷�B
				offsetX = PianoWhiteKeyWidth * 3 - PianoBlackKeyWidth * 0.5f;
				for (int i = 1; i <= x; i++)
				{
					offsetX += PianoWhiteKeyWidth;
					if ((i % 5) != 0 && (((i - (i / 5) * 5) + 1) % 3 == 0))
					{
						offsetX += PianoWhiteKeyWidth;
					}
					if ((i % 5) == 0 && (i != 0))
					{
						offsetX += PianoWhiteKeyWidth;
					}
				}
			}
		}
		else
		{
			int x = 0;
			for (int i = PianoKey::A0; i < m_NoteOnData.laneIndex; i++)
			{
				if (CMIDIInput::IsBlackKey(i))
				{
					continue;
				}
				x++;
			}
			offsetX = x * PianoWhiteKeyWidth;
		}

		int x = PianoRollOffsetX + offsetX;
		m_Rect = CRectangle(x, 0, x + width, 0);
		if (!m_bBlack)
		{
			m_Rect.Expansion(-PianoBlackKeyWidth * 0.5f, 0.0f);
		}
		else
		{
			m_Rect.Expansion(-PianoBlackKeyWidth * 0.1f, 0.0f);
		}

		// �S�I�[�g���A�Z�~�I�[�g�Ŕ͈͊O�̉��̏ꍇ�A�I�[�g��ON�ɂ���B
		m_bAuto = 
			(m_sAutoParam == Auto::All) ||
			(m_sAutoParam == Auto::Semi &&
			(m_NoteOnData.laneIndex < m_sKeyOffset || m_NoteOnData.laneIndex >= m_sKeyOffset + m_sKeyLength));

		// ���t����g���b�N���擾����B
		m_Channel = m_NoteOnData.trackNo;
	}

	void CNote::Start(const float& spd)
	{
		// �����̌v�Z�B
		float height = ((m_NoteOffData.eventTime - m_NoteOnData.eventTime) / 1000.0f) * (spd);
		m_Rect.Top   = -height;
		
		m_bStart = true;
		m_bShow  = true;
		m_bCheck = false;

		// ����p�S�[���^�C���̋L�^�B
		m_GoalTime = (CheckLineY / spd) + (m_NoteOnData.eventTime / 1000.0f);
	}

	void CNote::Update(const float& spd, const float& nowTime)
	{
		if (!m_bStart || !m_bShow)
		{
			return;
		}
		m_Rect.Translation(Vector2(0, spd * CUtilities::GetFrameSecond()));

		// �����łȂ��B
		if (m_bAuto)
		{
			AutoPlay();
		}

		// ����B
		if (!m_bCheck)
		{
			CheckCollision(nowTime);
		}
	}

	void CNote::Render(void) const
	{
		if (!m_bStart || !m_bShow)
		{
			return;
		}
		CGraphicsUtilities::RenderFillRect(
			m_Rect,
			m_bBlack ? MOF_XRGB(128, 255, 128) : MOF_XRGB(225, 255, 225),
			m_bBlack ? MOF_XRGB(128, 255, 128) : MOF_XRGB(225, 255, 225),
			m_bBlack ? MOF_XRGB( 96, 255,  96) : MOF_XRGB(128, 255, 128),
			m_bBlack ? MOF_XRGB( 96, 255,  96) : MOF_XRGB(128, 255, 128)
		);
		CGraphicsUtilities::RenderRect( m_Rect, MOF_COLOR_WHITE);
	}

	void CNote::AutoPlay(void)
	{
		if (m_Rect.Bottom > CheckLineY &&
			m_Rect.Top    < CheckLineY &&
			!g_MidiOutput.IsPlay((MofU8)m_NoteOnData.laneIndex, m_Channel))
		{
			g_MidiOutput.Play(0.5f, (MofU8)m_NoteOnData.laneIndex, m_Channel);
		}
		if (m_Rect.Top >= CheckLineY)
		{
			g_MidiOutput.Stop((MofU8)m_NoteOnData.laneIndex, m_Channel);
			m_bShow = false;
		}
	}

	void CNote::CheckCollision(const float& nowTime)
	{
		float checkTime = (m_GoalTime - nowTime);

		// �܂����C���܂ŗ��ĂȂ��B
		if (checkTime > BadTime)
		{
			// NONE
			return;
		}

		// �ʂ�߂��Ă�B
		else if (checkTime < -BadTime)
		{
			// MISS
			m_sHitResult = NoteHitResult::MISS;
			g_PlayResult.miss++;
			g_PlayResult.maxCombo = MOF_MAX(g_PlayResult.combo, g_PlayResult.maxCombo);
			g_PlayResult.combo = 0;
			if (m_pScore)
			{
				m_pScore->AddScore(ScoreNoteMiss);
			}
			m_bCheck = true;
			return;
		}

		checkTime = MOF_ABS(checkTime);
		
		// ���肷��B
		if (m_bAuto)
		{
			if (checkTime <= PerfectTime / 2.0f)
			{
				if (m_bPlayTrack)
				{
					m_sHitResult = NoteHitResult::PERFECT;
					g_PlayResult.perfect++;
					g_PlayResult.combo++;
				}
				m_bCheck = true;
			}
		}
		else if (g_MIDIInput.IsKeyPush((MofU8)m_NoteOnData.laneIndex))
		{
			if (checkTime <= PerfectTime / 2.0f)
			{
				// PERFECT
				m_sHitResult = NoteHitResult::PERFECT;
				g_PlayResult.perfect++;
				g_PlayResult.combo++;
				g_PlayResult.maxCombo = MOF_MAX(g_PlayResult.combo, g_PlayResult.maxCombo);
				m_pScore->AddScore(ScoreNoteParfect);
				m_bCheck = true;
			}
			else if (checkTime <= GreatTime / 2.0f)
			{
				// GREAT
				m_sHitResult = NoteHitResult::GREAT;
				g_PlayResult.great++;
				g_PlayResult.combo++;
				g_PlayResult.maxCombo = MOF_MAX(g_PlayResult.combo, g_PlayResult.maxCombo);
				m_pScore->AddScore(ScoreNoteGreat);
				m_bCheck = true;
			}
			else if (checkTime <= GoodTime / 2.0f)
			{
				// GOOD
				m_sHitResult = NoteHitResult::GOOD;
				g_PlayResult.good++;
				g_PlayResult.maxCombo = MOF_MAX(g_PlayResult.combo, g_PlayResult.maxCombo);
				g_PlayResult.combo = 0;
				m_pScore->AddScore(ScoreNoteGood);
				m_bCheck = true;
			}
			else if (checkTime <= BadTime / 2.0f)
			{
				// BAD
				m_sHitResult = NoteHitResult::BAD;
				g_PlayResult.bad++;
				g_PlayResult.maxCombo = MOF_MAX(g_PlayResult.combo, g_PlayResult.maxCombo);
				g_PlayResult.combo = 0;
				m_pScore->AddScore(ScoreNoteBad);
				m_bCheck = true;
			}
		}
	}

	void CNote::SetShow(const bool & b)
	{
		m_bShow = true;
	}

	void CNote::SetChannel(const MofU8 & channel)
	{
		m_Channel = channel;
	}

	void CNote::SetPlayTrack(const bool & b)
	{
		m_bPlayTrack = b;
	}

	void CNote::SetScore(CScore * pScore)
	{
		m_pScore = pScore;
	}

	bool CNote::IsStart(void) const
	{
		return m_bStart;
	}

	bool CNote::IsShow(void) const
	{
		return m_bShow;
	}

	int CNote::GetStartTime(void) const
	{
		return m_NoteOnData.eventTime;
	}

	CRectangle CNote::GetRect(void) const
	{
		return m_Rect;
	}

	NoteData CNote::GetNoteOnData(void) const
	{
		return m_NoteOnData;
	}

	void CNote::SetHitResult(NoteHitResult result)
	{
		m_sHitResult = result;
	}

	void CNote::SetAutoParam(Auto param)
	{
		m_sAutoParam = param;
	}

	void CNote::SetKeyOffset(PianoKey offset)
	{
		m_sKeyOffset = offset;
	}

	void CNote::SetKeyLength(KeyLength length)
	{
		m_sKeyLength = length;
	}

	Auto CNote::GetAutoParam(void)
	{
		return m_sAutoParam;
	}

	NoteHitResult CNote::GetHitResult(void)
	{
		return m_sHitResult;
	}

	CNoteArray::CNoteArray(void) :
		m_NoteArray(),
		m_SMFData(),
		m_StartPosOffset(0.0f),
		m_StopWatch()
	{
	}

	CNoteArray::~CNoteArray(void)
	{
	}

	bool CNoteArray::Load(LPCMofChar pName)
	{
		// �f�[�^�̏�����
		m_SMFData.Clear();

		return m_SMFData.Load(pName);
	}

	void CNoteArray::Initialize(const int& trackNo, CScore* pScore)
	{
		// ���t����g���b�N�̏��擾�B
		m_TrackNo = trackNo;

		// �������\���̔z��̍쐬�B
		CDynamicArray<CNote::InitState> initArray = CreateInitState(trackNo);

		m_NoteArray.ReSize(0);
		int cnt = initArray.GetArrayCount();
		for (int i = 0; i < cnt; i++)
		{
			m_NoteArray.Add(CNote(initArray[i]));
			m_NoteArray[i].SetPlayTrack(true);
			m_NoteArray[i].SetScore(pScore);
		}

		// �ق��̃g���b�N�ɉ��t��񂪂���ꍇ�̎������t�ݒ�B
		m_AutoNoteArray.ReSize(0);
		cnt = m_SMFData.GetNoteArray().GetArrayCount();

		Auto tmp = CNote::GetAutoParam();
		CNote::SetAutoParam(Auto::All);

		for (int i = 0; i < cnt; i++)
		{
			if (i == trackNo)
			{
				continue;
			}
			
			m_AutoNoteArray.Add();
			
			CDynamicArray<CNote::InitState> jInitArray = CreateInitState(i);

			m_AutoNoteArray[m_AutoNoteArray.GetArrayCount() - 1].ReSize(0);
			int jcnt = jInitArray.GetArrayCount();
			for (int j = 0; j < jcnt; j++)
			{
				m_AutoNoteArray[m_AutoNoteArray.GetArrayCount() - 1].Add(CNote(jInitArray[j]));
			}
		}

		CNote::SetAutoParam(tmp);

		m_TempoIndex = 0;
		m_BPM = m_SMFData.GetTempoArray()[m_TempoIndex++].bpm;

		CNote::SetHitResult(NoteHitResult::NONE);

		m_StopWatch.Start();
	}

	void CNoteArray::Update(void)
	{
		m_StopWatch.Update();

		// �e���|�����X�V����B
		int cnt = m_SMFData.GetTempoArray().GetArrayCount();
		if (m_TempoIndex < cnt)
		{
			// �e���|�ύX�C�x���g�������āA���Ԃ������Ȃ�BPM�ύX�I
			if (m_SMFData.GetTempoArray()[m_TempoIndex].eventTime < m_StopWatch.GetTime() * 1000)
			{
				m_BPM = m_SMFData.GetTempoArray()[m_TempoIndex++].bpm;
			}
		}

		cnt = m_NoteArray.GetArrayCount();
		for (int i = 0; i < cnt; i++)
		{
			if (!m_NoteArray[i].IsStart() && m_NoteArray[i].GetStartTime() < m_StopWatch.GetTime() * 1000)
			{
				m_NoteArray[i].Start(GetFallSpeed());
			}
			m_NoteArray[i].Update(GetFallSpeed(), m_StopWatch.GetTime());
		}

		// �������t�g
		for (int i = 0; i < m_AutoNoteArray.GetArrayCount(); i++)
		{
			for (int j = 0; j < m_AutoNoteArray[i].GetArrayCount(); j++)
			{
				if (!m_AutoNoteArray[i].GetData(j).IsStart() && m_AutoNoteArray[i].GetData(j).GetStartTime() < m_StopWatch.GetTime() * 1000)
				{
					m_AutoNoteArray[i].GetData(j).Start(GetFallSpeed());
				}
				m_AutoNoteArray[i].GetData(j).Update(GetFallSpeed(), m_StopWatch.GetTime());
			}
		}
	}

	void CNoteArray::Render(void) const
	{
		int cnt = m_NoteArray.GetArrayCount();
		for (int i = 0; i < cnt; i++)
		{
			m_NoteArray[i].Render();
		}
	}

	void CNoteArray::SetFallSpeed(const float & spd)
	{
		m_FallSpeed = 11.0f - MOF_CLIPING(spd, 1.0f, 10.0f);
	}

	int CNoteArray::GetBPM(void) const
	{
		return m_BPM;
	}

	float CNoteArray::GetFallSpeed(void) const
	{
		return CheckLineY / m_FallSpeed;
	}

	CSMFData& CNoteArray::GetSMFData(void)
	{
		return m_SMFData;
	}

	CDynamicArray<CNote> CNoteArray::GetNoteArray(void)
	{
		return m_NoteArray;
	}

	CDynamicArray<CNote::InitState> CNoteArray::CreateInitState(const int & trackNo)
	{

		// �m�[�c���̐��擾�B
		int cnt = m_SMFData.GetNoteArray()[trackNo].GetArrayCount();

		// �������\���̔z��̍쐬�B
		CDynamicArray<CNote::InitState> initArray;

		for (int i = 0; i < cnt; i++)
		{
			// �m�[�g�I�����b�Z�[�W������܂Ői�߂�B
			CNote::InitState init;
			NoteData on = m_SMFData.GetNoteArray()[trackNo].GetData(i);
			if (on.type == NoteType::LongStart)
			{
				init.noteOnData = on;
			}
			else
			{
				continue;
			}

			for (int j = i; j < cnt; j++)
			{
				// �m�[�g�I�t���b�Z�[�W���A�I�����b�Z�[�W�Ɖ��K�������ɂȂ�܂Ői�߂�B
				NoteData off = m_SMFData.GetNoteArray()[trackNo].GetData(j);
				if (on.laneIndex == off.laneIndex && off.type == NoteType::LongEnd)
				{
					init.noteOffData = off;
					initArray.Add(init);
					break;
				}
			}
		}

		return initArray;
	}

	bool LoadStanderdMidiFile(LPCMofChar pName, CNoteArray & array)
	{
		return array.Load(pName);
	}
}
