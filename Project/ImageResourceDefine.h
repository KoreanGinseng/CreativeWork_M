#pragma once
#include <iostream>

// �摜�f�[�^�̗񋓁B
enum IMAGE_RESOURCE
{

	BABY_BOY,

	IMAGE_RESOURCE_COUNT,

};

// �摜�f�[�^�̒�`�B
constexpr std::pair<char*, char*> ImageResource[IMAGE_RESOURCE_COUNT] = 
{
	{ "baby_boy", "baby_boy.png" },
};