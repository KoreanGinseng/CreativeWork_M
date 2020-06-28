#pragma once
#include "Mof.h"
#include <unordered_map>

namespace sip
{
	template <typename T > class CAssetBase
	{
	private:

		void operator= (const CAssetBase<T>&) = delete;

		std::unordered_map<std::string, std::shared_ptr<T>> m_AssetMap;


		CAssetBase(void) :
			m_AssetMap()
		{
		}

		static CAssetBase<T>& GetAssetMap(void)
		{
			static CAssetBase<T> assetMap;
			return assetMap;
		}

	public:

		~CAssetBase(void)
		{
			Release();
		}

		// ********************************************************************************
		/// <summary>
		/// アセットの登録。
		/// </summary>
		/// <param name="key">検索用キー</param>
		/// <param name="fileName">ファイル名</param>
		/// <returns>登録が成功すれば true それ以外 false </returns>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		static bool Load(const std::string& key, const std::string& fileName)
		{
			//if (GetAsset(key) == std::shared_ptr<T>())
			// (GetAsset(key) == empty)
			//if (!GetAsset(key))
			if (GetAssetMap().m_AssetMap.find(key) == GetAssetMap().m_AssetMap.end())
			{
				GetAssetMap().m_AssetMap[key] = std::make_shared<T>();
			}
			GetAssetMap().m_AssetMap[key]->Release();
			return GetAssetMap().m_AssetMap[key]->Load(fileName.c_str());
		}

		// ********************************************************************************
		/// <summary>
		/// 登録したキーからアセットの取得。
		/// </summary>
		/// <param name="key">キー</param>
		/// <returns>データを返す。データがない場合 empty を返す。</returns>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		static std::shared_ptr<T> GetAsset(const std::string& key)
		{
			return GetAssetMap().m_AssetMap[key];
		}

		// ********************************************************************************
		/// <summary>
		/// 全データの解放。
		/// </summary>
		/// <created>いのうえ,2020/04/26</created>
		/// <changed>いのうえ,2020/04/26</changed>
		// ********************************************************************************
		static void Release(void)
		{
			for (auto& itr : GetAssetMap().m_AssetMap)
			{
				itr.second->Release();
			}
		}
	};
	
	// アセットベースクラスに対応するようにしたフォントクラス
	class CFontA : public CFont
	{
	public:
		CFontA(void) : CFont() {}
		~CFontA(void) {}
		bool Load(LPCMofChar pName) { return CFont::Create(24, pName); }
	};

	//アセットの置き換え( bool Load() 関数 と Release() 関数が実装されていれば利用可能)
	typedef CAssetBase<CSoundBuffer>   CSoundAsset;
	typedef CAssetBase<CTexture>       CTextureAsset;
	typedef CAssetBase<CMeshContainer> CMeshAsset;
	typedef CAssetBase<CFontA>         CFontAsset;

	#define SoundAsset(key)            CSoundAsset::GetAsset(key)
	#define TextureAsset(key)          CTextureAsset::GetAsset(key)
	#define MeshAsset(key)             CMeshAsset::GetAsset(key)
	#define FontAsset(key)             CFontAsset::GetAsset(key)
}

using namespace sip;