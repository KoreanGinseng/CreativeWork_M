#include "WindowUtillities.h"

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
}

void CWindowUtillities::SetForeGround(const bool & b)
{
	HWND hWnd = g_pMainWindow->GetWindowHandle();

	HWND most = b ? HWND_TOPMOST : HWND_NOTOPMOST;

	// ç≈ëOñ ï\é¶ÇÃê›íË
	SetWindowPos(hWnd, most, 0, 0, 0, 0,
		(SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));
}
