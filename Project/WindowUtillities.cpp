#include "WindowUtillities.h"
#include "Common.h"

void CWindowUtillities::ToggleTitleBarEnable(void)
{
	HWND hWnd = g_pMainWindow->GetWindowHandle();

	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (dwStyle & WS_CAPTION)
	{
		dwStyle &= ~WS_CAPTION;
	}
	else
	{
		dwStyle |= WS_CAPTION;
	}

	SetWindowLong(hWnd, GWL_STYLE, dwStyle);

	SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
		(SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED));

	g_pGraphics->SetBackBufferSize(g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
}

void CWindowUtillities::SetForeGround(const bool & b)
{
	HWND hWnd = g_pMainWindow->GetWindowHandle();

	HWND most = b ? HWND_TOPMOST : HWND_NOTOPMOST;

	// Å‘O–Ê•\Ž¦‚ÌÝ’è
	SetWindowPos(hWnd, most, 0, 0, 0, 0,
		(SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));
}

WINDOWSIZE CWindowUtillities::GetWindowSize(void)
{
	int x = g_pGraphics->GetTargetWidth();
	return
		(x == WindowSize[WINDOWSIZE::LARGE].first)  ?
		WINDOWSIZE::LARGE  : 
		(x == WindowSize[WINDOWSIZE::MEDIUM].first) ?
		WINDOWSIZE::MEDIUM :
		WINDOWSIZE::SMALL  ;
}
