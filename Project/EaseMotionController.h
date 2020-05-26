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

	// 初期化。
	void Initialize(void)
	{
		Reset();
		m_bStart = false;

		// 全モーションの初期化。
		for (int i = 0; i < m_Array.GetArrayCount(); i++)
		{
			m_Array[i].Initialize();
		}
	}

	// モーションの開始。
	void Start(void)
	{
		m_bStart = true;

		// 配列に何も登録されていない場合終了フラグを立てて終了。
		if (m_Array.GetArrayCount() <= 0)
		{
			m_bEnd = true;
			return;
		}

		// 先頭から始める。
		m_SelectNo = 0;

		m_Array[m_SelectNo].Start();
	}

	// モーションの一時停止。
	void Stop(void)
	{
		// 配列に何も登録されていない場合終了。
		if (m_Array.GetArrayCount() <= 0)
		{
			return;
		}

		m_bStart = false;

		m_Array[m_SelectNo].Stop();
	}

	// モーションの再開。
	void Resume(void)
	{
		// 配列に何も登録されていない場合終了。
		if (m_Array.GetArrayCount() <= 0)
		{
			return;
		}

		m_bStart = true;

		m_Array[m_SelectNo].Resume();
	}

	// モーションのリセット。
	void Reset(void)
	{
		m_bEnd = false;

		m_SelectNo = 0;

		for (int i = 0; i < m_Array.GetArrayCount(); i++)
		{
			m_Array[i].Reset();
		}
	}

	// モーションの更新。
	void Update(void)
	{
		// 始まっていないなら更新しない。
		if (!m_bStart)
		{
			return;
		}

		// 選択中のモーションが終了している場合、次に進める。
		if (m_Array[m_SelectNo].IsEnd() && !m_bEnd)
		{
			// 終了したモーション番号を記憶しておく。
			int prevMotionNo = m_SelectNo;

			// 配列の境界外を参照しないようにする。
			m_SelectNo = MOF_MIN(m_SelectNo + 1, m_Array.GetArrayCount() - 1);

			// 配列の最後だった場合は終了フラグを立てて終了。
			if (m_SelectNo == prevMotionNo)
			{
				m_bEnd = true;
			}
			else
			{
				// 次のモーションをスタートさせる。
				m_Array[m_SelectNo].Start();
			}
		}

		// 各モーションの更新。
		for (int i = 0; i < m_Array.GetArrayCount(); i++)
		{
			m_Array[i].Update();
		}
	}

	// 開始フラグの取得。
	bool IsStart(void) const
	{
		return m_bStart;
	}

	// 終了フラグの取得。
	bool IsEnd(void) const
	{
		return m_bEnd;
	}

	// 先頭のアニメーションが始まってからの秒を返す。
	float GetTimer(void) const
	{
		return m_Array[0].GetTimer();
	}

	// 配列に登録されている個数を返す。
	int GetArrayCount(void) const
	{
		return m_Array.GetArrayCount();
	}

	// 現在のアニメーションの値を返す。
	T GetValue(void) const
	{
		return m_Array[m_SelectNo].GetValue();
	}

	// 配列にデータの追加。
	void Add(const CEaseMotion<T>& data)
	{
		m_Array.Add(data);
	}

	// 内部で Add 関数 を実行。
	void operator << (const CEaseMotion<T>& data)
	{
		Add(data);
	}

	// データを消す。
	void Clear(void)
	{
		m_Array.ReSize(0);
	}
};

