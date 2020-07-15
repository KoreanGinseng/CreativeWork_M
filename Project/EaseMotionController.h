#pragma once
#include "EaseMotion.h"

template <typename T > class CEaseMotionController
{
private:

	int                              m_SelectNo;

	CDynamicArray<CEaseMotion<T>>    m_Array;

	bool                             m_bStart;

	bool                             m_bEnd;

public:

	CEaseMotionController(void)	:
		m_SelectNo(0),
		m_Array(),
		m_bStart(false),
		m_bEnd(false)
	{
	}

	~CEaseMotionController(void)
	{
	}

	// �������B
	void Initialize(void)
	{
		Reset();
		m_bStart = false;

		// �S���[�V�����̏������B
		for (int i = 0; i < m_Array.GetArrayCount(); i++)
		{
			m_Array[i].Initialize();
		}
	}

	// ���[�V�����̊J�n�B
	void Start(void)
	{
		m_bStart = true;

		// �z��ɉ����o�^����Ă��Ȃ��ꍇ�I���t���O�𗧂ĂďI���B
		if (m_Array.GetArrayCount() <= 0)
		{
			m_bEnd = true;
			return;
		}

		// �擪����n�߂�B
		m_SelectNo = 0;

		m_Array[m_SelectNo].Start();
	}

	// ���[�V�����̈ꎞ��~�B
	void Stop(void)
	{
		// �z��ɉ����o�^����Ă��Ȃ��ꍇ�I���B
		if (m_Array.GetArrayCount() <= 0)
		{
			return;
		}

		m_bStart = false;

		m_Array[m_SelectNo].Stop();
	}

	// ���[�V�����̍ĊJ�B
	void Resume(void)
	{
		// �z��ɉ����o�^����Ă��Ȃ��ꍇ�I���B
		if (m_Array.GetArrayCount() <= 0)
		{
			return;
		}

		m_bStart = true;

		m_Array[m_SelectNo].Resume();
	}

	// ���[�V�����̃��Z�b�g�B
	void Reset(void)
	{
		m_bEnd = false;

		m_SelectNo = 0;

		for (int i = 0; i < m_Array.GetArrayCount(); i++)
		{
			m_Array[i].Reset();
		}
	}

	// ���[�V�����̍X�V�B
	void Update(void)
	{
		// �n�܂��Ă��Ȃ��Ȃ�X�V���Ȃ��B
		if (!m_bStart)
		{
			return;
		}

		// �I�𒆂̃��[�V�������I�����Ă���ꍇ�A���ɐi�߂�B
		if (m_Array[m_SelectNo].IsEnd() && !m_bEnd)
		{
			// �I���������[�V�����ԍ����L�����Ă����B
			int prevMotionNo = m_SelectNo;

			// �z��̋��E�O���Q�Ƃ��Ȃ��悤�ɂ���B
			m_SelectNo = MOF_MIN(m_SelectNo + 1, m_Array.GetArrayCount() - 1);

			// �z��̍Ōゾ�����ꍇ�͏I���t���O�𗧂ĂďI���B
			if (m_SelectNo == prevMotionNo)
			{
				m_bEnd = true;
			}
			else
			{
				// ���̃��[�V�������X�^�[�g������B
				m_Array[m_SelectNo].Start();
			}
		}

		// �e���[�V�����̍X�V�B
		for (int i = 0; i < m_Array.GetArrayCount(); i++)
		{
			m_Array[i].Update();
		}
	}

	// �J�n�t���O�̎擾�B
	bool IsStart(void) const
	{
		return m_bStart;
	}

	// �I���t���O�̎擾�B
	bool IsEnd(void) const
	{
		return m_bEnd;
	}

	// �擪�̃A�j���[�V�������n�܂��Ă���̕b��Ԃ��B
	float GetTimer(void) const
	{
		return m_Array[0].GetTimer();
	}

	// �z��ɓo�^����Ă������Ԃ��B
	int GetArrayCount(void) const
	{
		return m_Array.GetArrayCount();
	}

	// ���݂̃A�j���[�V�����̒l��Ԃ��B
	T GetValue(void) const
	{
		return m_Array[m_SelectNo].GetValue();
	}

	// �z��Ƀf�[�^�̒ǉ��B
	void Add(const CEaseMotion<T>& data)
	{
		m_Array.Add(data);
	}

	// ������ Add �֐� �����s�B
	void operator << (const CEaseMotion<T>& data)
	{
		Add(data);
	}

	// �f�[�^�������B
	void Clear(void)
	{
		m_Array.ReSize(0);
	}
};

