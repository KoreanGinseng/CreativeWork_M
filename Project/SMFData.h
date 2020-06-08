#pragma once
#include "Mof.h"
#include "MIDIDefine.h"

namespace sip
{
	// �w�b�_�`�����N�f�[�^�B
	// �t�@�C���̐擪�Ɉ�̂ݑ��݂���B
	struct HeaderChunkData
	{
		byte       chunkType[4];    // "MThd"�Ƃ��������񂪓����Ă���B      [ 4 byte ]
		MofU32     dataLength;      // 0x00000006 �������Ă���B             [ 4 byte ]
		MofU16     format;          // 0 or 1 or 2 �������Ă���B            [ 2 byte ]
		MofU16     trackCount;      // �g���b�N�`�����N�̐��������Ă���B    [ 2 byte ]
		MofU16     division;        // ����\�̃f�[�^�������Ă���B          [ 2 byte ]
	};

	// �g���b�N�`�����N�f�[�^�B
	struct TrackChunkData
	{
		byte       chunkType[4];    // "MTrk"�Ƃ��������񂪓����Ă���B      [ 4 byte ]
		MofU32     dataSize;        // �g���b�N�`�����N�̃T�C�Y�������Ă���B[ 4 byte ]
		byte*      pData;           // MIDI�f�[�^�̖{�̂������Ă���B        [ �ϒ� ]
	};

	// �m�[�c�̃^�C�v�B
	enum NoteType
	{
		LongStart,                  // �����O�J�n
		LongEnd,                    // �����O�I�[
	};

	// �m�[�c�f�[�^�B
	struct NoteData
	{
		int      eventTime;         // �m�[�c�^�C�~���O(ms)
		int      laneIndex;         // ���[���ԍ�
		NoteType type;              // �m�[�c�̎��
	};

	// �e���|�f�[�^�B
	struct TempoData
	{
		int   eventTime;            // BPM�ω��̃^�C�~���O(ms)
		float bpm;                  // BPM�l
		float tick;                 // tick�l
	};


	// �o�C�g��̃G���f�B�A���ϊ����s���֐��B
	constexpr void ByteSwap(byte* value, int size)
	{
		// �o�C�g�T�C�Y��1�ȉ����Ƃ��K�v�Ȃ��B
		if (size <= 1)
		{
			return;
		}

		// �ꎞ�I�ɕۑ����Ă����ϐ��B
		byte* temp = new byte[size];

		// �f�[�^�̃R�s�[�B
		for (int i = 0; i < size; i++)
		{
			temp[i] = value[i];
		}

		// �f�[�^�̓���ւ��B
		for (int i = 0; i < size; i++)
		{
			value[size - (i + 1)] = temp[i];
		}

		MOF_SAFE_DELETE_ARRAY(temp);
	}

	// ���g���G���f�B�A���ŕ���ł���o�C�g��𐔒l�^ T �ɒ����B
	template<typename T> T ConvertToNum(byte* value)
	{
		// �߂�l��p�ӂ���B
		T re = 0;

		// �߂�l�̃o�C�g�����擾����B
		int size = sizeof(T);

		// �o�C�g����������Ă����B
		for (int i = 0; i < size; i++)
		{
			re |= value[i] << 8 * i;
		}
		return re;
	}

	class CSMFData
	{
	private:

		MofU16                   m_MaxTrackNum;  // �g���b�N�̐��B
		MofU16                   m_Resolution;   // ����\�̒l�B

		CDynamicArray<NoteData>  m_NoteArray;
		CDynamicArray<TempoData> m_TempoArray;

	public:

		CSMFData(void);

		~CSMFData(void);

		// SMF(.mid)�t�@�C����ǂݍ��ފ֐��B
		bool Load(LPCMofChar pFileName);

		// �f�[�^�̃N���A�B
		void Clear(void);

		CDynamicArray<NoteData>& GetNoteArray(void);

		CDynamicArray<TempoData>& GetTempoArray(void);

	private:

		// �g���b�N�f�[�^�̉�͂��s���֐��B
		void TrackDataAnalysis(byte* pData, const int& size, const HeaderChunkData& hcd);

		// �C�x���g�^�C���̍Čv�Z���s���֐��B
		void ModificationEventTimes(void);

	};
}

