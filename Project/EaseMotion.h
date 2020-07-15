#pragma once
#include "Easing.h"

template <typename T > class CEaseMotion
{
protected:

	float              m_Timer;
			           
	T                  m_Value;

	T                  m_Begin;
	
	T                  m_End;
			           
	bool               m_bStart;

	bool               m_bEnd;
			           
	float              m_MotionTime;
			           
	Ease               m_Ease;
			           
	EaseType           m_EaseType;

public:

	CEaseMotion(void) :
		m_Timer(0.0f),
		m_Value(),
		m_Begin(),
		m_End(),
		m_bStart(false),
		m_bEnd(false),
		m_MotionTime(1.0f),
		m_Ease(Ease::In),
		m_EaseType(EaseType::Sine)
	{
	}

	//         (        開始値,       終了値,       イージング,       イージング種類,    開始から終了までの秒 )
	CEaseMotion(const T& begin, const T& end, const Ease& ease, const EaseType& type, const float& time = 1.0f)
	{
		SetBeginEnd(begin, end);
		SetEase(ease, type);
		SetMotionTime(time);
	}

	virtual ~CEaseMotion(void)
	{
	}

	//初期化
	virtual void Initialize(void)
	{
		Reset();
		m_bStart = false;
	}

	// 初めからスタートする。
	virtual void Start(void)
	{
		Reset();
		m_bStart = true;
	}

	// 一時停止する。
	virtual void Stop(void)
	{
		m_bStart = false;
	}

	// 再開する。
	virtual void Resume(void)
	{
		m_bStart = true;
	}

	virtual void Update(void)
	{
		// 始まっていないなら更新しない。
		if (!m_bStart)
		{
			return;
		}

		// タイマーの加算
		m_Timer += CUtilities::GetFrameSecond();

		// タイマーから指定した秒数で 0.0f ~ 1.0f に動くように計算する。
		const float timer = m_Timer / m_MotionTime;

		// タイマーから 0.0f ～ 1.0f を取得する。
		const float t = MOF_MIN(timer, 1.0f);

		// タイマーが 1 秒を超えているなら終了フラグを立てる。
		m_bEnd = (t >= 1.0f);

		// タイマーを使ってイージングする。
		const float e = Easing::Easing(m_Ease, m_EaseType, t);

		// イージングの値で線形補間。
		m_Value = MOF_LERP(m_Begin, m_End, e);
	}

	// モーションのリセット。
	virtual void Reset(void)
	{
		m_bEnd = false;

		ResetTimer();
	}

	// タイマーのリセット。
	virtual void ResetTimer(void)
	{
		m_Timer = 0.0f;
	}

	// モーションする時間を指定する。(秒)
	virtual void SetMotionTime(const float& second)
	{
		m_MotionTime = second;
	}

	virtual void SetBeginEnd(const T& begin, const T& end)
	{
		m_Begin = begin;
		m_End   = end;
	}

	virtual void SetEase(const Ease& ease)
	{
		m_Ease = ease;
	}

	virtual void SetEase(const Ease& ease, const EaseType& easeType)
	{
		SetEase(ease);
		SetEaseType(easeType);
	}

	virtual void SetEaseType(const EaseType& easeType)
	{
		m_EaseType = easeType;
	}

	T GetValue(void) const
	{
		return m_Value;
	}

	// スタートしてからの経過時間を返す。(秒)
	float GetTimer(void) const
	{
		return m_Timer;
	}

	bool IsEnd(void) const
	{
		return m_bEnd;
	}

	bool IsStart(void) const
	{
		return m_bStart;
	}
};

