#pragma once
#include "Mof.h"
#include "MIDIDefine.h"

namespace sip
{
	// ヘッダチャンクデータ。
	// ファイルの先頭に一つのみ存在する。
	struct HeaderChunkData
	{
		byte       chunkType[4];    // "MThd"という文字列が入っている。      [ 4 byte ]
		MofU32     dataLength;      // 0x00000006 が入っている。             [ 4 byte ]
		MofU16     format;          // 0 or 1 or 2 が入っている。            [ 2 byte ]
		MofU16     trackCount;      // トラックチャンクの数が入っている。    [ 2 byte ]
		MofU16     division;        // 分解能のデータが入っている。          [ 2 byte ]
	};

	// トラックチャンクデータ。
	struct TrackChunkData
	{
		byte       chunkType[4];    // "MTrk"という文字列が入っている。      [ 4 byte ]
		MofU32     dataSize;        // トラックチャンクのサイズが入っている。[ 4 byte ]
		byte*      pData;           // MIDIデータの本体が入っている。        [ 可変長 ]
	};

	// ノーツのタイプ。
	enum NoteType
	{
		LongStart,                  // ロング開始
		LongEnd,                    // ロング終端
	};

	// ノーツデータ。
	struct NoteData
	{
		int      eventTime;         // ノーツタイミング(ms)
		int      laneIndex;         // レーン番号
		NoteType type;              // ノーツの種類
	};

	// テンポデータ。
	struct TempoData
	{
		int   eventTime;            // BPM変化のタイミング(ms)
		float bpm;                  // BPM値
		float tick;                 // tick値
	};


	// バイト列のエンディアン変換を行う関数。
	constexpr void ByteSwap(byte* value, int size)
	{
		// バイトサイズが1以下だとやる必要なし。
		if (size <= 1)
		{
			return;
		}

		// 一時的に保存しておく変数。
		byte* temp = new byte[size];

		// データのコピー。
		for (int i = 0; i < size; i++)
		{
			temp[i] = value[i];
		}

		// データの入れ替え。
		for (int i = 0; i < size; i++)
		{
			value[size - (i + 1)] = temp[i];
		}

		MOF_SAFE_DELETE_ARRAY(temp);
	}

	// リトルエンディアンで並んでいるバイト列を数値型 T に直す。
	template<typename T> T ConvertToNum(byte* value)
	{
		// 戻り値を用意する。
		T re = 0;

		// 戻り値のバイト数を取得する。
		int size = sizeof(T);

		// バイト数だけ入れていく。
		for (int i = 0; i < size; i++)
		{
			re |= value[i] << 8 * i;
		}
		return re;
	}

	class CSMFData
	{
	private:

		MofU16                   m_MaxTrackNum;  // トラックの数。
		MofU16                   m_Resolution;   // 分解能の値。

		CDynamicArray<NoteData>  m_NoteArray;
		CDynamicArray<TempoData> m_TempoArray;

	public:

		CSMFData(void);

		~CSMFData(void);

		// SMF(.mid)ファイルを読み込む関数。
		bool Load(LPCMofChar pFileName);

		// データのクリア。
		void Clear(void);

		CDynamicArray<NoteData>& GetNoteArray(void);

		CDynamicArray<TempoData>& GetTempoArray(void);

	private:

		// トラックデータの解析を行う関数。
		void TrackDataAnalysis(byte* pData, const int& size, const HeaderChunkData& hcd);

		// イベントタイムの再計算を行う関数。
		void ModificationEventTimes(void);

	};
}

