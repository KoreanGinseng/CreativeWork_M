#include	"GameApp.h"

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;

	Info.WindowCreateInfo.Title  = "M";

	Info.WindowCreateInfo.Width  = 600;
	Info.WindowCreateInfo.Height = 450;

	Info.GraphicsCreateInfo.bMSAA = FALSE;

	Info.pApplication = new CGameApp();
	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}