#include "StopWatch.h"

using namespace sip;

CStopWatch::CStopWatch(void) :
	m_bStart(false),
	m_Time(0.0f)
{
}

CStopWatch::~CStopWatch(void)
{
}

void CStopWatch::Start(void)
{
	Reset();
	m_bStart = true;
}

void CStopWatch::Stop(void)
{
	m_bStart = false;
}

void CStopWatch::Resume(void)
{
	m_bStart = true;
}

void CStopWatch::Reset(void)
{
	SetTime(0.0f);
}

void CStopWatch::Update(void)
{
	if (!m_bStart)
	{
		return;
	}

	m_Time += CUtilities::GetFrameSecond();
}

bool CStopWatch::IsStart(void) const
{
	return m_bStart;
}

float CStopWatch::GetTime(void) const
{
	return m_Time;
}

void CStopWatch::SetTime(const float & t)
{
	m_Time = t;
}
