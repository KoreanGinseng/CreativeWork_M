#pragma once
#include <iostream>

// �����敪�̗񋓁B
enum GROW_KEY
{
	BABY  = 0b0000, // �c��
	CHILD = 0b0001, // �q�ǂ�
	YOUNG = 0b0010, // �N
	ADULT = 0b0100, // ���l
	ELDER = 0b1000, // �V�l
};


// �}�ӂɓo�^�����L�����N�^�[�񋓁B
enum CHARACTER_GUITE 
{

	BABY_BOY              = 0b00000000,

};


// �����敪���������璲�ׂ�֐��B
char GetGrowKey(const short& guideNo)
{
	return guideNo >> 4;
}