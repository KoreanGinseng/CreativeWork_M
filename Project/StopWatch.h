#pragma once
#include "Mof.h"

namespace sip
{
	class CStopWatch
	{
	private:

		bool m_bStart;

		float m_Time;

	public:

		CStopWatch(void);

		~CStopWatch(void);

		void Start(void);

		void Stop(void);

		void Resume(void);

		void Reset(void);

		void Update(void);

		bool IsStart(void) const;

		// �P�ʂ͕b
		float GetTime(void) const;

		// �P�ʂ͕b
		void SetTime(const float& t);
	};
}
