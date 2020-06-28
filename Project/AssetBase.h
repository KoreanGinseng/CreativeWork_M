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
		/// �A�Z�b�g�̓o�^�B
		/// </summary>
		/// <param name="key">�����p�L�[</param>
		/// <param name="fileName">�t�@�C����</param>
		/// <returns>�o�^����������� true ����ȊO false </returns>
		/// <created>���̂���,2020/04/26</created>
		/// <changed>���̂���,2020/04/26</changed>
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
		/// �o�^�����L�[����A�Z�b�g�̎擾�B
		/// </summary>
		/// <param name="key">�L�[</param>
		/// <returns>�f�[�^��Ԃ��B�f�[�^���Ȃ��ꍇ empty ��Ԃ��B</returns>
		/// <created>���̂���,2020/04/26</created>
		/// <changed>���̂���,2020/04/26</changed>
		// ********************************************************************************
		static std::shared_ptr<T> GetAsset(const std::string& key)
		{
			return GetAssetMap().m_AssetMap[key];
		}

		// ********************************************************************************
		/// <summary>
		/// �S�f�[�^�̉���B
		/// </summary>
		/// <created>���̂���,2020/04/26</created>
		/// <changed>���̂���,2020/04/26</changed>
		// ********************************************************************************
		static void Release(void)
		{
			for (auto& itr : GetAssetMap().m_AssetMap)
			{
				itr.second->Release();
			}
		}
	};
	
	// �A�Z�b�g�x�[�X�N���X�ɑΉ�����悤�ɂ����t�H���g�N���X
	class CFontA : public CFont
	{
	public:
		CFontA(void) : CFont() {}
		~CFontA(void) {}
		bool Load(LPCMofChar pName) { return CFont::Create(24, pName); }
	};

	//�A�Z�b�g�̒u������( bool Load() �֐� �� Release() �֐�����������Ă���Η��p�\)
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