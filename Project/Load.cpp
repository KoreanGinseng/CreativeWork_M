#include "Load.h"

CLoad::CLoad(const CLoad::InitData & init) :
	CLoadBase(init)
{
	// 初期化処理
}

CLoad::~CLoad(void)
{
	// 解放処理
}

void CLoad::Update(void)
{
	// 読み込み中の更新処理。


	// スレッドでの読み込み制御。
	CLoadBase::Update();
}

void CLoad::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Loading");
}
