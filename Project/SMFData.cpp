#include "SMFData.h"

namespace sip
{
	CSMFData::CSMFData(void)
	{
	}

	CSMFData::~CSMFData(void)
	{
	}

	bool CSMFData::Load(LPCMofChar pFileName)
	{
		// ファイルオープン！！！
		FILE* fp = fopen(pFileName, "rb");

		// 開封に失敗した場合、すぐに帰る。
		if (fp == NULL)
		{
			return false;
		}

#pragma region "ヘッダチャンク部分の読み込み。"

		// ヘッダチャンク部分の読み込み。
		HeaderChunkData hcd;

		// ヘッダのチャンクタイプを取得する。"MThd"これ入ってる。
		fread(hcd.chunkType, sizeof(byte) * 4, 1, fp);

		// データの長さを取得する。なんで6固定なんだろうね。6固定なら1バイトか2バイトでいいと思う。
		byte byteArray[4];
		fread(byteArray, sizeof(char) * 4, 1, fp);

		// ビッグエンディアンで格納されているのでリトルエンディアンへ変換する。
		ByteSwap(byteArray, 4);

		// 変換後のデータを保存する。特に意味ないと思う。
		hcd.dataLength = ConvertToNum<MofU32>(byteArray);

		// フォーマットの取得。 0 or 1 or 2 のやつ。 2 はほとんどないらしい。
		byte shortArray[2];
		fread(shortArray, sizeof(char) * 2, 1, fp);

		// 変換やつ。
		ByteSwap(shortArray, 2);

		// とりあえず保存する。
		hcd.format = ConvertToNum<MofU16>(shortArray);

		// フォーマットごとにトラックの扱いが違う。 2 は複雑ということと、ほとんど使われていないことから考慮しないことにした。
		// フォーマットが 0 の場合、すべてのチャンネルのデータを一つのトラックにまとめている。つまり、トラック数は必然的に 1 になる。
		fread(shortArray, sizeof(char) * 2, 1, fp);
		ByteSwap(shortArray, 2);
		m_MaxTrackNum = ConvertToNum<MofU16>(shortArray);

		// 時間単位の取得。(分解能の取得)
		// 最初のビットが 0 なら、何小節の何拍目のデータ方式でトラックチャンクが作られている。
		// 最初のビットが 1 なら、何分何秒のデータ方式で保存する。
		fread(shortArray, sizeof(char) * 2, 1, fp);
		ByteSwap(shortArray, 2);
		MofU16 solution = ConvertToNum<MofU16>(shortArray);

		// 1 は未対応
		if (solution & 0x8000) // 1
		{
			// 14 ～ 8 ビットは 4 つの標準的な SMPTE と MIDI タイムコードのフォーマットに相応して、
			// -24, -25, -29, あるいは -30 の4つの値のうちの一つ ( -29 は 30 ドロップ・フレームに相当) を含み、秒ごとのフレーム数を表す。
			byte frameParSec = ((solution & 0x7F00) >> 8);
			byte tickParFrame = (solution & 0x00FF);

			// こっちの形式よくわかんねぇええ

		}
		else
		{
			hcd.division = solution;
			m_Resolution = hcd.division;
		}

#pragma endregion

#pragma region "トラックチャンク部分の読み込み。"

		// トラック分メモリを確保する。
		TrackChunkData* pTrackData = new TrackChunkData[m_MaxTrackNum];

		// トラックの数だけ読み込む。
		for (int i = 0; i < m_MaxTrackNum; i++)
		{
			// チャンクタイプ取得。"MTrk"がくるんだよね。
			fread(pTrackData[i].chunkType, sizeof(byte) * 4, 1, fp);

			// トラックデータの長さを取得しちゃうぞ。
			byte byteArray[4];
			fread(byteArray, sizeof(byte) * 4, 1, fp);

			// エンディアン変換！！
			ByteSwap(byteArray, 4);

			// 数値型に直して保存！！
			pTrackData[i].dataSize = ConvertToNum<MofU32>(byteArray);

			// データの分だけメモリ確保だぜぃ。
			pTrackData[i].pData = new byte[pTrackData[i].dataSize];

			// トラックデータを一気に読みこんじゃうぞい！
			fread(pTrackData[i].pData, sizeof(byte) * (pTrackData[i].dataSize), 1, fp);

			// 必要な情報だけを保存していくぜ！！
			TrackDataAnalysis(pTrackData[i].pData, pTrackData[i].dataSize, hcd);

			// メモリ解放するよおおおお。
			if (pTrackData[i].dataSize > 1)
			{
				MOF_SAFE_DELETE_ARRAY(pTrackData[i].pData);
			}
			else
			{
				MOF_SAFE_DELETE(pTrackData[i].pData);
			}
		}

		// メモリ解放するよおおおお。
		if (m_MaxTrackNum > 1)
		{
			MOF_SAFE_DELETE_ARRAY(pTrackData);
		}
		else
		{
			MOF_SAFE_DELETE(pTrackData);
		}

#pragma endregion

		// 開けたら閉めようホトトギス。
		fclose(fp);

		// イベントタイムを再計算する。
		ModificationEventTimes();

		// ここまでくれば関数的には成功。
		return true;
	}

	void CSMFData::Clear(void)
	{
		m_MaxTrackNum = 0;
		m_Resolution  = 0;
		m_NoteArray.ReSize(0);
		m_TempoArray.ReSize(0);
	}

	CDynamicArray<NoteData>& CSMFData::GetNoteArray(void)
	{
		return m_NoteArray;
	}

	CDynamicArray<TempoData>& CSMFData::GetTempoArray(void)
	{
		return m_TempoArray;
	}

	void CSMFData::TrackDataAnalysis(byte * pData, const int & size, const HeaderChunkData & hcd)
	{
		MofUInt currentTime = 0;     // デルタタイムを足していく、つまり現在の時間(ms)（ノーツやソフランのイベントタイムはこれを使う）
		byte    statusByte  = 0x00;  // ステータスバイト
		bool    bRunning    = false; // ランニングステータスチェック用フラグ
		bool    bEnd        = false; // トラック終了フラグ

		for (int i = 0; i < size && !bEnd;)
		{
			// このイベントでのデルタタイム。
			MofUInt deltaTime = 0;

#pragma region "デルタタイム解析"

			// デルタタイムの解析。
			while (true)
			{
				// デルタタイムの取得。
				byte delta = pData[i];

				// 下位 7 ビットがデルタタイムなので下位 7 ビットを加算していく。
				deltaTime |= (delta & 0x7F);

				// 先頭ビットが立っていれば次のデータもデルタタイムである。
				if ((pData[i] & 0x80) == 0)
				{
					// インデックスを進める。
					i++;
					break;
				}

				// 次のデルタタイムを収納するため、ビットをずらしてやる。
				deltaTime <<= 7;

				// インデックスを進める。
				i++;
			}

			// 現在の時間にデルタタイムを足す。
			currentTime += deltaTime;

#pragma endregion

#pragma region "イベントステータス解析"
			
			// イベントステータスの解析。
			// ランニングステータスフラグが立っていないのであればステータスバイトをチェックする。
			if (!bRunning)
			{
				statusByte = pData[i++];

				// ランニングステータスは、MIDIイベントのみ有効なのでそれ以外のイベントフラグだった場合は無視する。
				// MIDIイベントかつ、最上位Bitが立っているなら、ランニングステータスといえる。
				bRunning = 
					!(statusByte & Event::Meta)     && 
					!(statusByte & Event::SysEx_F7) && 
					!(statusByte & Event::SysEx)    &&
					(statusByte & 0x80);
			}

#pragma endregion

			if (statusByte == Event::Meta)
			{
#pragma region "メタイベント解析"

				// メタイベント取得とインデックスを進めておく。
				byte metaIventID = pData[i++];

				switch (metaIventID)
				{
				case MetaEvent::Sequence_Nunber:
				{
					// バイトの長さを取得する。( 2 固定 )
					byte length = pData[i++];
					
					byte byteArray[2];
					byteArray[1] = pData[i++];
					byteArray[0] = pData[i++];

					// ここの2バイトにはシーケンス番号になっている。
					MofU16 sequence = ConvertToNum<MofU16>(byteArray);

					break;
				}
				case MetaEvent::Comment:
				{
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];

					// テキストメッセージは処理しないため、データサイズだけインデックスを進める。
					i += length;

					break;
				}
				case MetaEvent::Copy_Right:
				{
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];

					// コピーライトは後で使う予定なので取得はしておく。
					char* pText = new char[length + 1];

					for (int textIndex = 0; textIndex < length; textIndex++)
					{
						pText[textIndex] = pData[i++];
					}

					// 文字列終端文字を入れておく。
					pText[length] = '\0';

					// TODO : ここで文字列を保存する処理。

					// メモリ確保したら解放もする。
					if (length > 1)
					{
						MOF_SAFE_DELETE_ARRAY(pText);
					}
					else
					{
						MOF_SAFE_DELETE(pText);
					}

					break;
				}
				case MetaEvent::Sequence_Track_Name:
				{
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];

					// フォーマット0またはフォーマット1の第1トラックの場合、
					// 曲名を表す。それ以外はトラック名を表す。

					// TODO : フォーマット判定、トラック番号判定

					// 曲名は後で使う予定なので取得はしておく。
					char* pText = new char[length + 1];

					for (int textIndex = 0; textIndex < length; textIndex++)
					{
						pText[textIndex] = pData[i++];
					}

					// 文字列終端文字を入れておく。
					pText[length] = '\0';

					// TODO : ここで文字列を保存する処理。

					// メモリ確保したら解放もする。
					if (length > 1)
					{
						MOF_SAFE_DELETE_ARRAY(pText);
					}
					else
					{
						MOF_SAFE_DELETE(pText);
					}

					break;
				}
				case MetaEvent::Instrument_Name:
				{
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];

					// 楽器名は処理しないため、データサイズだけインデックスを進める。
					i += length;

					break;
				}
				case MetaEvent::Lyric:
				{
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];

					// 歌詞は処理しないため、データサイズだけインデックスを進める。
					i += length;
					break;
				}
				case MetaEvent::Marker:
				{
					// 通常フォーマット0のトラック、あるいはフォーマット1の第1トラック中に置く。
					// シーケンス中のそのポイントの名前である。
					// まあ、これも処理しないのでデータサイズだけ進めまっす。
					
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Queue_Point:
				{
					// 楽曲スコア中のこのポイントでスコア以外に起きていることが書かれている。
					// これも無視する。
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Program_Name:
				{
					// SMF規格1.0には記載がなかったたよ。遺物らしいよ。
					// データが来ても困るので処理はしておく。
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Device_Name:
				{
					// SMF規格1.0には記載がなかったたよ。
					// データが来ても困るので処理はしておく。
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Channel_Prefix:
				{
					// バイトの長さを取得する。( 1 固定 )
					byte length = pData[i++];

					// MIDIチャンネル番号が入ってるらしい。次に進もう。
					byte cc = pData[i++];

					break;
				}
				case MetaEvent::Port_Specified:
				{
					// SMF規格1.0には記載がなかったたよ。

					// バイトの長さを取得する。( 1 固定 )
					byte length = pData[i++];
					
					// 出力ポートらしい。
					byte pp     = pData[i++];
					
					break;
				}
				case MetaEvent::End_Of_Track:
				{
					// トラックの終わりを示すところでございます。
					bEnd = true;

					break;
				}
				case MetaEvent::Set_Tempo:
				{
					// バイトの長さを取得する。( 3 固定 )
					byte length = pData[i++];

					// テンポ変更情報リストに格納する。
					TempoData tempoData;
					tempoData.eventTime = currentTime;

					// ４分音符の長さをマイクロ秒単位で格納されている。
					byte tempoArray[3];
					tempoArray[2] = pData[i++];
					tempoArray[1] = pData[i++];
					tempoArray[0] = pData[i++];

					MofU32 tempo = (tempoArray[2] << 16) | (tempoArray[1] << 8) | (tempoArray[0]);

					// BPM割り出し。
					tempoData.bpm = 60000000 / (float)tempo;

					// 小数点第1で切り捨て処理(10にすると第一位、100にすると第2位まで切り捨てられる)
					tempoData.bpm = std::floor(tempoData.bpm * 10.0f) / 10.0f;

					// tick値割り出し。
					tempoData.tick = (60 / tempoData.bpm / hcd.division * 1000);

					// リストにつっこむ。
					m_TempoArray.Add(tempoData);

					break;
				}
				case MetaEvent::Smtpte_Offset:
				{
					// バイトの長さを取得する。( 5 固定 )
					byte length = pData[i++];

					// 扱い方がわからないのでとりあえずとばそう。
					i += length;

					break;
				}
				case MetaEvent::Time_Signature:
				{
					// バイトの長さを取得する。( 4 固定 )
					byte length = pData[i++];

					// 分子
					byte nn = pData[i++];

					// 分母 ( 2 の累乗 )
					byte dd = pData[i++];

					int bunbo = 1;
					for (int x = 0; x < dd; x++)
					{
						bunbo *= 2;
					}

					// ひとつのメトロノーム・クロック中のMIDIクロックの数を表す。
					byte cc = pData[i++];

					// ひとつのMIDI4分音符(24MIDIクロック)中で表記される32分音符の数を表す。
					byte bb = pData[i++];

					break;
				}
				case MetaEvent::Key_Signature:
				{
					// バイトの長さを取得する。( 2 固定 )
					byte length = pData[i++];

					// -7 : 7♭, -1 : 1♭, 0 : C調, 1 : 1♯, 7 : 7♯
					byte sf = pData[i++];

					// 0 : 長調, 1 : 短調
					byte mi = pData[i++];

					break;
				}
				case MetaEvent::Special_Meta_Event:
				{
					// バイトの長さを取得する。( 可変長 )
					byte length = pData[i++];

					// 基本１Byteだけど、０だった場合、３Byteである。
					if (length == 0)
					{
						length = 0x03;
					}
					
					// これも読むつもりないのでとばす。
					i += length;

					break;
				}
				default:
				case MetaEvent::FF_None:
				{
					// わけわからんイベント。ここきたら終わり。何もわからん。
					break;
				}
				}

#pragma endregion
			}
			else if (statusByte == Event::SysEx || statusByte == Event::SysEx_F7)
			{
#pragma region "システムエクスクルーシブイベント解析"

				// 読む必要なさそうなのでとばす。
				byte length = pData[i++];
				i += length;

#pragma endregion
			}
			else
			{
#pragma region "MIDIイベント解析"

				switch (statusByte & 0xF0)
				{
				case Event::MIDI_Note_Off:
				{
					// 鍵盤の押された位置。
					byte keyNote = pData[i++];

					// 大きさ( 64 固定 )
					byte velocity = pData[i++];

					// 長押し終わりノーツ情報生成。
					NoteData offNote;
					offNote.eventTime = currentTime;
					offNote.laneIndex = keyNote;
					offNote.type = NoteType::LongEnd;

					// リストにぶち込むんやで。
					m_NoteArray.Add(offNote);

					break;
				}
				case Event::MIDI_Note_On:
				{
					// 鍵盤の押された位置。
					byte keyNote = pData[i++];

					// 鍵盤をおす強さ。
					byte velocity = pData[i++];

					// 長押し開始ノーツ情報生成。
					NoteData onNote;
					onNote.eventTime = currentTime;
					onNote.laneIndex = keyNote;
					onNote.type = NoteType::LongStart;

					// ベロシティが０ならノートオフ情報として扱うため、データのタイプを変える。
					if (velocity == 0)
					{
						onNote.type = NoteType::LongEnd;
					}

					// リストに情報を追加してやる。
					m_NoteArray.Add(onNote);

					break;
				}
				case Event::MIDI_PolyPhonic_Key_Pressure:
				{
					// 使わないのでスルースルー。
					i += 2;
					break;
				}
				case Event::MIDI_Control:
				{
					// コントロールする番号。
					byte ctrlNo = pData[i++];

					// 設定する値。
					byte value = pData[i++];

					// ※0x00-0x77までがコントロールチェンジで、それ以上はチャンネルモードメッセージとして処理する。
					if (ctrlNo < 0x78)
					{
						// コントロールチェンジ。
					}
					else
					{
						// チャンネルモードメッセージは一律データバイトを2つ使用している。
						// チャンネルモードメッセージ。
						switch (ctrlNo)
						{
						case 0x78:  // オールサウンドオフ。
							// 該当するチャンネルの発音中の音を直ちに消音する。後述のオールノートオフより強制力が強い。
							break;

						case 0x79:  // リセットオールコントローラ。
							// 該当するチャンネルの全種類のコントロール値を初期化する。
							break;

						case 0x7A:  // ローカルコントロール。
							// オフ:鍵盤を弾くとMIDIメッセージは送信されるがピアノ自体から音は出ない。
							// オン:鍵盤を弾くと音源から音が出る(基本こっち)
							break;

						case 0x7B:  // オールノートオフ。
							// 該当するチャンネルの発音中の音すべてに対してノートオフ命令を出す。
							break;

							/* MIDIモード設定 */
							// オムニのオン・オフとモノ・ポリモードを組み合わせて4種類のモードがある。
						case 0x7C:  // オムニモードオフ
							break;
						case 0x7D:  // オムニモードオン
							break;
						case 0x7E:  // モノモードオン
							break;
						case 0x7F:  // モノモードオン
							break;
						}
					}
					break;
				}
				case Event::MIDI_Program_Change:
				{
					// 音色。
					byte instrument = pData[i++];

					break;
				}
				case Event::MIDI_Channel_Pressure:
				{
					// プレッシャー情報らしい。
					byte pressure = pData[i++];

					break;
				}
				case Event::MIDI_Pitch_Bend:
				{
					// ここの値はリトルエンディアンだそうで。
					byte byteArray[2];
					byteArray[0] = pData[i++];
					byteArray[1] = pData[i++];
					MofU16 pitch = ConvertToNum<MofU16>(byteArray);

					break;
				}
				}

#pragma endregion
			}
		}
	}

	void CSMFData::ModificationEventTimes(void)
	{
		// 一時格納用（計算前の時間を保持したいため）
		CDynamicArray<TempoData> tempTempoList = m_TempoArray;

		// テンポイベント時間修正
		int tcnt = m_TempoArray.GetArrayCount();
		for (int i = 1; i < tcnt; i++)
		{
			TempoData tempo = m_TempoArray[i];

			int timeDifference = tempTempoList[i].eventTime - tempTempoList[i - 1].eventTime;
			tempo.eventTime = (int)(timeDifference * m_TempoArray[i - 1].tick) + m_TempoArray[i - 1].eventTime;

			m_TempoArray[i] = tempo;
		}

		// ノーツイベント時間修正
		int ncnt = m_NoteArray.GetArrayCount();
		for (int i = 0; i < ncnt; i++)
		{
			for (int j = tcnt - 1; j >= 0; j--)
			{
				if (m_NoteArray[i].eventTime >= tempTempoList[j].eventTime)
				{
					NoteData note = m_NoteArray[i];

					int timeDifference = m_NoteArray[i].eventTime - tempTempoList[j].eventTime;
					note.eventTime = (int)(timeDifference * tempTempoList[j].tick) + m_TempoArray[j].eventTime;   // 計算後のテンポ変更イベント時間+そこからの自分の時間
					m_NoteArray[i] = note;
					break;
				}
			}
		}
	}

}