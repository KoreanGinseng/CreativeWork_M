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
		// �t�@�C���I�[�v���I�I�I
		FILE* fp = fopen(pFileName, "rb");

		// �J���Ɏ��s�����ꍇ�A�����ɋA��B
		if (fp == NULL)
		{
			return false;
		}

#pragma region "�w�b�_�`�����N�����̓ǂݍ��݁B"

		// �w�b�_�`�����N�����̓ǂݍ��݁B
		HeaderChunkData hcd;

		// �w�b�_�̃`�����N�^�C�v���擾����B"MThd"��������Ă�B
		fread(hcd.chunkType, sizeof(byte) * 4, 1, fp);

		// �f�[�^�̒������擾����B�Ȃ��6�Œ�Ȃ񂾂낤�ˁB6�Œ�Ȃ�1�o�C�g��2�o�C�g�ł����Ǝv���B
		byte byteArray[4];
		fread(byteArray, sizeof(char) * 4, 1, fp);

		// �r�b�O�G���f�B�A���Ŋi�[����Ă���̂Ń��g���G���f�B�A���֕ϊ�����B
		ByteSwap(byteArray, 4);

		// �ϊ���̃f�[�^��ۑ�����B���ɈӖ��Ȃ��Ǝv���B
		hcd.dataLength = ConvertToNum<MofU32>(byteArray);

		// �t�H�[�}�b�g�̎擾�B 0 or 1 or 2 �̂�B 2 �͂قƂ�ǂȂ��炵���B
		byte shortArray[2];
		fread(shortArray, sizeof(char) * 2, 1, fp);

		// �ϊ���B
		ByteSwap(shortArray, 2);

		// �Ƃ肠�����ۑ�����B
		hcd.format = ConvertToNum<MofU16>(shortArray);

		// �t�H�[�}�b�g���ƂɃg���b�N�̈������Ⴄ�B 2 �͕��G�Ƃ������ƂƁA�قƂ�ǎg���Ă��Ȃ����Ƃ���l�����Ȃ����Ƃɂ����B
		// �t�H�[�}�b�g�� 0 �̏ꍇ�A���ׂẴ`�����l���̃f�[�^����̃g���b�N�ɂ܂Ƃ߂Ă���B�܂�A�g���b�N���͕K�R�I�� 1 �ɂȂ�B
		fread(shortArray, sizeof(char) * 2, 1, fp);
		ByteSwap(shortArray, 2);
		m_MaxTrackNum = ConvertToNum<MofU16>(shortArray);

		// ���ԒP�ʂ̎擾�B(����\�̎擾)
		// �ŏ��̃r�b�g�� 0 �Ȃ�A�����߂̉����ڂ̃f�[�^�����Ńg���b�N�`�����N������Ă���B
		// �ŏ��̃r�b�g�� 1 �Ȃ�A�������b�̃f�[�^�����ŕۑ�����B
		fread(shortArray, sizeof(char) * 2, 1, fp);
		ByteSwap(shortArray, 2);
		MofU16 solution = ConvertToNum<MofU16>(shortArray);

		// 1 �͖��Ή�
		if (solution & 0x8000) // 1
		{
			// 14 �` 8 �r�b�g�� 4 �̕W���I�� SMPTE �� MIDI �^�C���R�[�h�̃t�H�[�}�b�g�ɑ������āA
			// -24, -25, -29, ���邢�� -30 ��4�̒l�̂����̈�� ( -29 �� 30 �h���b�v�E�t���[���ɑ���) ���܂݁A�b���Ƃ̃t���[������\���B
			byte frameParSec = ((solution & 0x7F00) >> 8);
			byte tickParFrame = (solution & 0x00FF);

			// �������̌`���悭�킩��˂�����

		}
		else
		{
			hcd.division = solution;
			m_Resolution = hcd.division;
		}

#pragma endregion

#pragma region "�g���b�N�`�����N�����̓ǂݍ��݁B"

		// �g���b�N�����������m�ۂ���B
		TrackChunkData* pTrackData = new TrackChunkData[m_MaxTrackNum];

		// �g���b�N�̐������ǂݍ��ށB
		for (int i = 0; i < m_MaxTrackNum; i++)
		{
			// �`�����N�^�C�v�擾�B"MTrk"������񂾂�ˁB
			fread(pTrackData[i].chunkType, sizeof(byte) * 4, 1, fp);

			// �g���b�N�f�[�^�̒������擾�����Ⴄ���B
			byte byteArray[4];
			fread(byteArray, sizeof(byte) * 4, 1, fp);

			// �G���f�B�A���ϊ��I�I
			ByteSwap(byteArray, 4);

			// ���l�^�ɒ����ĕۑ��I�I
			pTrackData[i].dataSize = ConvertToNum<MofU32>(byteArray);

			// �f�[�^�̕������������m�ۂ������B
			pTrackData[i].pData = new byte[pTrackData[i].dataSize];

			// �g���b�N�f�[�^����C�ɓǂ݂��񂶂Ⴄ�����I
			fread(pTrackData[i].pData, sizeof(byte) * (pTrackData[i].dataSize), 1, fp);

			// �K�v�ȏ�񂾂���ۑ����Ă������I�I
			TrackDataAnalysis(pTrackData[i].pData, pTrackData[i].dataSize, hcd);

			// �������������您�������B
			if (pTrackData[i].dataSize > 1)
			{
				MOF_SAFE_DELETE_ARRAY(pTrackData[i].pData);
			}
			else
			{
				MOF_SAFE_DELETE(pTrackData[i].pData);
			}
		}

		// �������������您�������B
		if (m_MaxTrackNum > 1)
		{
			MOF_SAFE_DELETE_ARRAY(pTrackData);
		}
		else
		{
			MOF_SAFE_DELETE(pTrackData);
		}

#pragma endregion

		// �J������߂悤�z�g�g�M�X�B
		fclose(fp);

		// �C�x���g�^�C�����Čv�Z����B
		ModificationEventTimes();

		// �����܂ł���Ί֐��I�ɂ͐����B
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
		MofUInt currentTime = 0;     // �f���^�^�C���𑫂��Ă����A�܂茻�݂̎���(ms)�i�m�[�c��\�t�����̃C�x���g�^�C���͂�����g���j
		byte    statusByte  = 0x00;  // �X�e�[�^�X�o�C�g
		bool    bRunning    = false; // �����j���O�X�e�[�^�X�`�F�b�N�p�t���O
		bool    bEnd        = false; // �g���b�N�I���t���O

		for (int i = 0; i < size && !bEnd;)
		{
			// ���̃C�x���g�ł̃f���^�^�C���B
			MofUInt deltaTime = 0;

#pragma region "�f���^�^�C�����"

			// �f���^�^�C���̉�́B
			while (true)
			{
				// �f���^�^�C���̎擾�B
				byte delta = pData[i];

				// ���� 7 �r�b�g���f���^�^�C���Ȃ̂ŉ��� 7 �r�b�g�����Z���Ă����B
				deltaTime |= (delta & 0x7F);

				// �擪�r�b�g�������Ă���Ύ��̃f�[�^���f���^�^�C���ł���B
				if ((pData[i] & 0x80) == 0)
				{
					// �C���f�b�N�X��i�߂�B
					i++;
					break;
				}

				// ���̃f���^�^�C�������[���邽�߁A�r�b�g�����炵�Ă��B
				deltaTime <<= 7;

				// �C���f�b�N�X��i�߂�B
				i++;
			}

			// ���݂̎��ԂɃf���^�^�C���𑫂��B
			currentTime += deltaTime;

#pragma endregion

#pragma region "�C�x���g�X�e�[�^�X���"
			
			// �C�x���g�X�e�[�^�X�̉�́B
			// �����j���O�X�e�[�^�X�t���O�������Ă��Ȃ��̂ł���΃X�e�[�^�X�o�C�g���`�F�b�N����B
			if (!bRunning)
			{
				statusByte = pData[i++];

				// �����j���O�X�e�[�^�X�́AMIDI�C�x���g�̂ݗL���Ȃ̂ł���ȊO�̃C�x���g�t���O�������ꍇ�͖�������B
				// MIDI�C�x���g���A�ŏ��Bit�������Ă���Ȃ�A�����j���O�X�e�[�^�X�Ƃ�����B
				bRunning = 
					!(statusByte & Event::Meta)     && 
					!(statusByte & Event::SysEx_F7) && 
					!(statusByte & Event::SysEx)    &&
					(statusByte & 0x80);
			}

#pragma endregion

			if (statusByte == Event::Meta)
			{
#pragma region "���^�C�x���g���"

				// ���^�C�x���g�擾�ƃC���f�b�N�X��i�߂Ă����B
				byte metaIventID = pData[i++];

				switch (metaIventID)
				{
				case MetaEvent::Sequence_Nunber:
				{
					// �o�C�g�̒������擾����B( 2 �Œ� )
					byte length = pData[i++];
					
					byte byteArray[2];
					byteArray[1] = pData[i++];
					byteArray[0] = pData[i++];

					// ������2�o�C�g�ɂ̓V�[�P���X�ԍ��ɂȂ��Ă���B
					MofU16 sequence = ConvertToNum<MofU16>(byteArray);

					break;
				}
				case MetaEvent::Comment:
				{
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];

					// �e�L�X�g���b�Z�[�W�͏������Ȃ����߁A�f�[�^�T�C�Y�����C���f�b�N�X��i�߂�B
					i += length;

					break;
				}
				case MetaEvent::Copy_Right:
				{
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];

					// �R�s�[���C�g�͌�Ŏg���\��Ȃ̂Ŏ擾�͂��Ă����B
					char* pText = new char[length + 1];

					for (int textIndex = 0; textIndex < length; textIndex++)
					{
						pText[textIndex] = pData[i++];
					}

					// ������I�[���������Ă����B
					pText[length] = '\0';

					// TODO : �����ŕ������ۑ����鏈���B

					// �������m�ۂ�������������B
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
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];

					// �t�H�[�}�b�g0�܂��̓t�H�[�}�b�g1�̑�1�g���b�N�̏ꍇ�A
					// �Ȗ���\���B����ȊO�̓g���b�N����\���B

					// TODO : �t�H�[�}�b�g����A�g���b�N�ԍ�����

					// �Ȗ��͌�Ŏg���\��Ȃ̂Ŏ擾�͂��Ă����B
					char* pText = new char[length + 1];

					for (int textIndex = 0; textIndex < length; textIndex++)
					{
						pText[textIndex] = pData[i++];
					}

					// ������I�[���������Ă����B
					pText[length] = '\0';

					// TODO : �����ŕ������ۑ����鏈���B

					// �������m�ۂ�������������B
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
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];

					// �y�햼�͏������Ȃ����߁A�f�[�^�T�C�Y�����C���f�b�N�X��i�߂�B
					i += length;

					break;
				}
				case MetaEvent::Lyric:
				{
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];

					// �̎��͏������Ȃ����߁A�f�[�^�T�C�Y�����C���f�b�N�X��i�߂�B
					i += length;
					break;
				}
				case MetaEvent::Marker:
				{
					// �ʏ�t�H�[�}�b�g0�̃g���b�N�A���邢�̓t�H�[�}�b�g1�̑�1�g���b�N���ɒu���B
					// �V�[�P���X���̂��̃|�C���g�̖��O�ł���B
					// �܂��A������������Ȃ��̂Ńf�[�^�T�C�Y�����i�߂܂����B
					
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Queue_Point:
				{
					// �y�ȃX�R�A���̂��̃|�C���g�ŃX�R�A�ȊO�ɋN���Ă��邱�Ƃ�������Ă���B
					// �������������B
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Program_Name:
				{
					// SMF�K�i1.0�ɂ͋L�ڂ��Ȃ���������B�╨�炵����B
					// �f�[�^�����Ă�����̂ŏ����͂��Ă����B
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Device_Name:
				{
					// SMF�K�i1.0�ɂ͋L�ڂ��Ȃ���������B
					// �f�[�^�����Ă�����̂ŏ����͂��Ă����B
					byte length = pData[i++];
					i += length;

					break;
				}
				case MetaEvent::Channel_Prefix:
				{
					// �o�C�g�̒������擾����B( 1 �Œ� )
					byte length = pData[i++];

					// MIDI�`�����l���ԍ��������Ă�炵���B���ɐi�����B
					byte cc = pData[i++];

					break;
				}
				case MetaEvent::Port_Specified:
				{
					// SMF�K�i1.0�ɂ͋L�ڂ��Ȃ���������B

					// �o�C�g�̒������擾����B( 1 �Œ� )
					byte length = pData[i++];
					
					// �o�̓|�[�g�炵���B
					byte pp     = pData[i++];
					
					break;
				}
				case MetaEvent::End_Of_Track:
				{
					// �g���b�N�̏I���������Ƃ���ł������܂��B
					bEnd = true;

					break;
				}
				case MetaEvent::Set_Tempo:
				{
					// �o�C�g�̒������擾����B( 3 �Œ� )
					byte length = pData[i++];

					// �e���|�ύX��񃊃X�g�Ɋi�[����B
					TempoData tempoData;
					tempoData.eventTime = currentTime;

					// �S�������̒������}�C�N���b�P�ʂŊi�[����Ă���B
					byte tempoArray[3];
					tempoArray[2] = pData[i++];
					tempoArray[1] = pData[i++];
					tempoArray[0] = pData[i++];

					MofU32 tempo = (tempoArray[2] << 16) | (tempoArray[1] << 8) | (tempoArray[0]);

					// BPM����o���B
					tempoData.bpm = 60000000 / (float)tempo;

					// �����_��1�Ő؂�̂ď���(10�ɂ���Ƒ��ʁA100�ɂ���Ƒ�2�ʂ܂Ő؂�̂Ă���)
					tempoData.bpm = std::floor(tempoData.bpm * 10.0f) / 10.0f;

					// tick�l����o���B
					tempoData.tick = (60 / tempoData.bpm / hcd.division * 1000);

					// ���X�g�ɂ����ށB
					m_TempoArray.Add(tempoData);

					break;
				}
				case MetaEvent::Smtpte_Offset:
				{
					// �o�C�g�̒������擾����B( 5 �Œ� )
					byte length = pData[i++];

					// ���������킩��Ȃ��̂łƂ肠�����Ƃ΂����B
					i += length;

					break;
				}
				case MetaEvent::Time_Signature:
				{
					// �o�C�g�̒������擾����B( 4 �Œ� )
					byte length = pData[i++];

					// ���q
					byte nn = pData[i++];

					// ���� ( 2 �̗ݏ� )
					byte dd = pData[i++];

					int bunbo = 1;
					for (int x = 0; x < dd; x++)
					{
						bunbo *= 2;
					}

					// �ЂƂ̃��g���m�[���E�N���b�N����MIDI�N���b�N�̐���\���B
					byte cc = pData[i++];

					// �ЂƂ�MIDI4������(24MIDI�N���b�N)���ŕ\�L�����32�������̐���\���B
					byte bb = pData[i++];

					break;
				}
				case MetaEvent::Key_Signature:
				{
					// �o�C�g�̒������擾����B( 2 �Œ� )
					byte length = pData[i++];

					// -7 : 7��, -1 : 1��, 0 : C��, 1 : 1��, 7 : 7��
					byte sf = pData[i++];

					// 0 : ����, 1 : �Z��
					byte mi = pData[i++];

					break;
				}
				case MetaEvent::Special_Meta_Event:
				{
					// �o�C�g�̒������擾����B( �ϒ� )
					byte length = pData[i++];

					// ��{�PByte�����ǁA�O�������ꍇ�A�RByte�ł���B
					if (length == 0)
					{
						length = 0x03;
					}
					
					// ������ǂނ���Ȃ��̂łƂ΂��B
					i += length;

					break;
				}
				default:
				case MetaEvent::FF_None:
				{
					// �킯�킩���C�x���g�B����������I���B�����킩���B
					break;
				}
				}

#pragma endregion
			}
			else if (statusByte == Event::SysEx || statusByte == Event::SysEx_F7)
			{
#pragma region "�V�X�e���G�N�X�N���[�V�u�C�x���g���"

				// �ǂޕK�v�Ȃ������Ȃ̂łƂ΂��B
				byte length = pData[i++];
				i += length;

#pragma endregion
			}
			else
			{
#pragma region "MIDI�C�x���g���"

				switch (statusByte & 0xF0)
				{
				case Event::MIDI_Note_Off:
				{
					// ���Ղ̉����ꂽ�ʒu�B
					byte keyNote = pData[i++];

					// �傫��( 64 �Œ� )
					byte velocity = pData[i++];

					// �������I���m�[�c��񐶐��B
					NoteData offNote;
					offNote.eventTime = currentTime;
					offNote.laneIndex = keyNote;
					offNote.type = NoteType::LongEnd;

					// ���X�g�ɂԂ����ނ��ŁB
					m_NoteArray.Add(offNote);

					break;
				}
				case Event::MIDI_Note_On:
				{
					// ���Ղ̉����ꂽ�ʒu�B
					byte keyNote = pData[i++];

					// ���Ղ����������B
					byte velocity = pData[i++];

					// �������J�n�m�[�c��񐶐��B
					NoteData onNote;
					onNote.eventTime = currentTime;
					onNote.laneIndex = keyNote;
					onNote.type = NoteType::LongStart;

					// �x���V�e�B���O�Ȃ�m�[�g�I�t���Ƃ��Ĉ������߁A�f�[�^�̃^�C�v��ς���B
					if (velocity == 0)
					{
						onNote.type = NoteType::LongEnd;
					}

					// ���X�g�ɏ���ǉ����Ă��B
					m_NoteArray.Add(onNote);

					break;
				}
				case Event::MIDI_PolyPhonic_Key_Pressure:
				{
					// �g��Ȃ��̂ŃX���[�X���[�B
					i += 2;
					break;
				}
				case Event::MIDI_Control:
				{
					// �R���g���[������ԍ��B
					byte ctrlNo = pData[i++];

					// �ݒ肷��l�B
					byte value = pData[i++];

					// ��0x00-0x77�܂ł��R���g���[���`�F���W�ŁA����ȏ�̓`�����l�����[�h���b�Z�[�W�Ƃ��ď�������B
					if (ctrlNo < 0x78)
					{
						// �R���g���[���`�F���W�B
					}
					else
					{
						// �`�����l�����[�h���b�Z�[�W�͈ꗥ�f�[�^�o�C�g��2�g�p���Ă���B
						// �`�����l�����[�h���b�Z�[�W�B
						switch (ctrlNo)
						{
						case 0x78:  // �I�[���T�E���h�I�t�B
							// �Y������`�����l���̔������̉��𒼂��ɏ�������B��q�̃I�[���m�[�g�I�t��苭���͂������B
							break;

						case 0x79:  // ���Z�b�g�I�[���R���g���[���B
							// �Y������`�����l���̑S��ނ̃R���g���[���l������������B
							break;

						case 0x7A:  // ���[�J���R���g���[���B
							// �I�t:���Ղ�e����MIDI���b�Z�[�W�͑��M����邪�s�A�m���̂��特�͏o�Ȃ��B
							// �I��:���Ղ�e���Ɖ������特���o��(��{������)
							break;

						case 0x7B:  // �I�[���m�[�g�I�t�B
							// �Y������`�����l���̔������̉����ׂĂɑ΂��ăm�[�g�I�t���߂��o���B
							break;

							/* MIDI���[�h�ݒ� */
							// �I���j�̃I���E�I�t�ƃ��m�E�|�����[�h��g�ݍ��킹��4��ނ̃��[�h������B
						case 0x7C:  // �I���j���[�h�I�t
							break;
						case 0x7D:  // �I���j���[�h�I��
							break;
						case 0x7E:  // ���m���[�h�I��
							break;
						case 0x7F:  // ���m���[�h�I��
							break;
						}
					}
					break;
				}
				case Event::MIDI_Program_Change:
				{
					// ���F�B
					byte instrument = pData[i++];

					break;
				}
				case Event::MIDI_Channel_Pressure:
				{
					// �v���b�V���[���炵���B
					byte pressure = pData[i++];

					break;
				}
				case Event::MIDI_Pitch_Bend:
				{
					// �����̒l�̓��g���G���f�B�A���������ŁB
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
		// �ꎞ�i�[�p�i�v�Z�O�̎��Ԃ�ێ����������߁j
		CDynamicArray<TempoData> tempTempoList = m_TempoArray;

		// �e���|�C�x���g���ԏC��
		int tcnt = m_TempoArray.GetArrayCount();
		for (int i = 1; i < tcnt; i++)
		{
			TempoData tempo = m_TempoArray[i];

			int timeDifference = tempTempoList[i].eventTime - tempTempoList[i - 1].eventTime;
			tempo.eventTime = (int)(timeDifference * m_TempoArray[i - 1].tick) + m_TempoArray[i - 1].eventTime;

			m_TempoArray[i] = tempo;
		}

		// �m�[�c�C�x���g���ԏC��
		int ncnt = m_NoteArray.GetArrayCount();
		for (int i = 0; i < ncnt; i++)
		{
			for (int j = tcnt - 1; j >= 0; j--)
			{
				if (m_NoteArray[i].eventTime >= tempTempoList[j].eventTime)
				{
					NoteData note = m_NoteArray[i];

					int timeDifference = m_NoteArray[i].eventTime - tempTempoList[j].eventTime;
					note.eventTime = (int)(timeDifference * tempTempoList[j].tick) + m_TempoArray[j].eventTime;   // �v�Z��̃e���|�ύX�C�x���g����+��������̎����̎���
					m_NoteArray[i] = note;
					break;
				}
			}
		}
	}

}