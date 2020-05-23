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

		// 単位は秒
		float GetTime(void) const;

		// 単位は秒
		void SetTime(const float& t);
	};
}
