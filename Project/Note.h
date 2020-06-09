#pragma once
#include "MIDIInput.h"
#include "MIDIOut.h"
#include "StopWatch.h"
#include "SMFData.h"

namespace sip
{
	enum class NoteHitResult
	{
		NONE    = -1,
		MISS    =  0,
		BAD     =  1,
		GOOD    =  2,
		GREAT   =  3,
		PERFECT =  4,
	};

	enum KeyLength
	{
		_25 = 25,
		_37 = 37,
		_49 = 49,
		_61 = 61,
		_88 = 88
	};

	enum Auto
	{
		All,

		Semi,

		None
	};

	constexpr float PerfectTime = 0.033f;

	constexpr float GreatTime   = 0.150f;
	
	constexpr float GoodTime    = 0.350f;

	constexpr float BadTime     = 0.783f;

	class CNote
	{
	public:

		struct InitState
		{
			NoteData    noteOnData;

			NoteData    noteOffData;
		};

	private:

		CRectangle  m_Rect;

		bool        m_bStart;

		bool        m_bBlack;

		bool        m_bShow;

		bool        m_bAuto;

		bool        m_bCheck;

		NoteData    m_NoteOnData;

		NoteData    m_NoteOffData;

		float       m_GoalTime;

		static NoteHitResult m_sHitResult;

		static Auto          m_sAutoParam;

		static PianoKey      m_sKeyOffset;

		static KeyLength     m_sKeyLength;

	public:

		CNote(void);

		CNote(const InitState& state);

		~CNote(void);

		void Initialize(const InitState& state);

		void Start(const float& spd);

		void Update(const float& spd, const float& nowTime);

		void Render(void) const;

		void AutoPlay(void);

		void CheckCollision(const float& nowTime);

		void SetShow(const bool& b);

		bool IsStart(void) const;

		bool IsShow(void) const;

		int GetStartTime(void) const;

		CRectangle GetRect(void) const;

		NoteData GetNoteOnData(void) const;

		static void SetHitResult(NoteHitResult result);

		static void SetAutoParam(Auto param);
		
		static void SetKeyOffset(PianoKey offset);
		
		static void SetKeyLength(KeyLength length);

		static NoteHitResult GetHitResult(void);

	};

	class CNoteArray
	{
	private:

		CDynamicArray<CNote>     m_NoteArray;

		float                    m_StartPosOffset;

		sip::CStopWatch          m_StopWatch;

		CSMFData                 m_SMFData;

		float                    m_FallSpeed;

		float                    m_GoalTime;

		int                      m_BPM;

		int                      m_TempoIndex;

	public:

		CNoteArray(void);

		virtual ~CNoteArray(void);

		bool Load(LPCMofChar pName);

		void Initialize(const int& trackNo);

		void Update(void);

		void Render(void) const;

		void SetFallSpeed(const float& spd);

		int GetBPM(void) const;

		float GetFallSpeed(void) const;

		CSMFData GetSMFData(void);

		CDynamicArray<CNote> GetNoteArray(void);

	};

	bool LoadStanderdMidiFile(LPCMofChar pName, CNoteArray& array);
}
