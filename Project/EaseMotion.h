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

	//         (        �J�n�l,       �I���l,       �C�[�W���O,       �C�[�W���O���,    �J�n����I���܂ł̕b )
	CEaseMotion(const T& begin, const T& end, const Ease& ease, const EaseType& type, const float& time = 1.0f)
	{
		SetBeginEnd(begin, end);
		SetEase(ease, type);
		SetMotionTime(time);
	}

	virtual ~CEaseMotion(void)
	{
	}

	//������
	virtual void Initialize(void)
	{
		Reset();
		m_bStart = false;
	}

	// ���߂���X�^�[�g����B
	virtual void Start(void)
	{
		Reset();
		m_bStart = true;
	}

	// �ꎞ��~����B
	virtual void Stop(void)
	{
		m_bStart = false;
	}

	// �ĊJ����B
	virtual void Resume(void)
	{
		m_bStart = true;
	}

	virtual void Update(void)
	{
		// �n�܂��Ă��Ȃ��Ȃ�X�V���Ȃ��B
		if (!m_bStart)
		{
			return;
		}

		// �^�C�}�[�̉��Z
		m_Timer += CUtilities::GetFrameSecond();

		// �^�C�}�[����w�肵���b���� 0.0f ~ 1.0f �ɓ����悤�Ɍv�Z����B
		const float timer = m_Timer / m_MotionTime;

		// �^�C�}�[���� 0.0f �` 1.0f ���擾����B
		const float t = MOF_MIN(timer, 1.0f);

		// �^�C�}�[�� 1 �b�𒴂��Ă���Ȃ�I���t���O�𗧂Ă�B
		m_bEnd = (t >= 1.0f);

		// �^�C�}�[���g���ăC�[�W���O����B
		const float e = Easing::Easing(m_Ease, m_EaseType, t);

		// �C�[�W���O�̒l�Ő��`��ԁB
		m_Value = MOF_LERP(m_Begin, m_End, e);
	}

	// ���[�V�����̃��Z�b�g�B
	virtual void Reset(void)
	{
		m_bEnd = false;

		ResetTimer();
	}

	// �^�C�}�[�̃��Z�b�g�B
	virtual void ResetTimer(void)
	{
		m_Timer = 0.0f;
	}

	// ���[�V�������鎞�Ԃ��w�肷��B(�b)
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

	// �X�^�[�g���Ă���̌o�ߎ��Ԃ�Ԃ��B(�b)
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

