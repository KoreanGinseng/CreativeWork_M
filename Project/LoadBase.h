#pragma once
#include "Common.h"

using LoadFunction = std::function<bool(void)>;

class CLoadThread : public CThread
{
private:

	bool                      m_bSuccess = false;

	bool                      m_bEnd = false;

	LoadFunction              m_Func;

public:

	CLoadThread(void) : CThread() {}

	~CLoadThread(void) {}

	virtual void Run(void) override
	{
		m_bSuccess = false;
		m_bEnd     = false;

		m_bSuccess = m_Func();

		m_bEnd     = true;
	}

	// スレッドで実行する読み込み関数の登録。
	void SetFunc(const LoadFunction& func)
	{
		m_Func = func;
	}

	const bool IsSuccess(void) const noexcept
	{
		return m_bSuccess;
	}

	const bool IsEnd(void) const noexcept
	{
		return m_bEnd;
	}
};

class CLoadBase : public MyApp::CScene
{
private:

	CLoadThread                                            m_Thread;

	static std::string                                     m_LoadFuncName;
	
	static SceneName                                       m_NextKey;

	static std::unordered_map<std::string, LoadFunction>   m_LoadFuncMap;

public:

	CLoadBase(const CLoadBase::InitData& init);

	virtual ~CLoadBase(void);

	virtual void Update(void) override;

	virtual void Render(void) override = 0;

	// 読み込み関数の登録。
	static void SetLoadFunc(const std::string& key, const LoadFunction& func);

	// 読み込みが終わったあとの次のシーンの設定。
	static void SetNextScene(const SceneName& next);

	// 登録されている関数から、読み込みを行う関数の指定。
	static void SetLoadFuncName(const std::string& key);
};

