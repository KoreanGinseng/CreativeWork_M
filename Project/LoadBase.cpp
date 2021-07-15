#include "LoadBase.h"

std::string CLoadBase::m_LoadFuncName = "";

SceneName CLoadBase::m_NextKey;

std::unordered_map<std::string, LoadFunction> CLoadBase::m_LoadFuncMap;


CLoadBase::CLoadBase(const CLoadBase::InitData & init) :
	IScene(init)
{
	m_Thread.SetFunc(m_LoadFuncMap[m_LoadFuncName]);
	m_Thread.Start("GameLoadingThread");
}

CLoadBase::~CLoadBase(void)
{
	m_Thread.Release();
}

void CLoadBase::Update(void)
{
	// スレッドで読み込み処理が終わってなければここで終わる。
	if (!m_Thread.IsEnd())
	{
		return;
	}

	// スレッド読み込みが終わって関数で失敗している場合、アプリケーションの終了。
	if (!m_Thread.IsSuccess())
	{
		MessageBox(NULL, "読み込みに失敗しました。", "エラー", MB_ICONERROR | MB_OK);
		PostQuitMessage(3);
	}

	// 読み込みが成功で終わった場合、次のシーンへ行く。
	ChangeScene(m_NextKey);
}

void CLoadBase::Render(void)
{
}

void CLoadBase::SetLoadFunc(const std::string & key, const LoadFunction & func)
{
	m_LoadFuncMap[key] = func;
}

void CLoadBase::SetNextScene(const SceneName & next)
{
	m_NextKey = next;
}

void CLoadBase::SetLoadFuncName(const std::string & key)
{
	m_LoadFuncName = key;
}
