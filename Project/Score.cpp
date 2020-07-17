#include "Score.h"

CScore::CScore(void) :
	m_Score(0),
	m_MaxCombo(0)
{
}

CScore::~CScore(void)
{
}

int CScore::GetScore(void) const
{
	return m_Score;
}

int CScore::GetMaxCombo(void) const
{
	return m_MaxCombo;
}

CScore & CScore::SetScore(const int & score)
{
	m_Score = score;
	return *this;
}

CScore & CScore::SetMaxCombo(const int & maxCombo)
{
	m_MaxCombo = maxCombo;
	return *this;
}

CScore & CScore::AddScore(const int & add)
{
	m_Score += add;
	return *this;
}

CScoreManager::CScoreManager(void)
{
}

CScoreManager::~CScoreManager(void)
{
}

CScoreManager & CScoreManager::GetManager(void)
{
	static CScoreManager manager;
	return manager;
}

bool CScoreManager::Load(LPCMofChar pName)
{
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}

	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* pBuffer = new char[fSize + 1];

	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	// 保存されている曲の数。
	pstr    = strtok(pBuffer, ",");
	int cnt = atoi(pstr);

	for (int i = 0; i < cnt; i++)
	{
		ScoreKey key;

		// TRUCK
		pstr       = strtok(NULL, ",");
		key.second = atoi(pstr);

		// TITLE
		pstr       = strtok(NULL, ",");
		key.first  = std::string(pstr);

		// HISCORE
		pstr       = strtok(NULL, ",");
		CScoreManager::GetScore(key).SetScore(atoi(pstr));

		// MAXCOMBO
		pstr       = strtok(NULL, ",");
		CScoreManager::GetScore(key).SetMaxCombo(atoi(pstr));
	}
	
	MOF_SAFE_DELETE_ARRAY(pBuffer);

	fclose(fp);

	return true;
}

bool CScoreManager::Save(LPCMofChar pName)
{
	FILE* fp = fopen(pName, "wt");
	if (fp == NULL)
	{
		return false;
	}
	int cnt = GetManager().m_ScoreMap.size();
	fprintf(fp, "%d,\n", cnt);

	for (const auto& itr : GetManager().m_ScoreMap)
	{
		const ScoreKey& key = itr.first;
		const CScore& value = itr.second;

		// タイトルを先に保存すると、改行を考慮しないといけなくなるため、トラック番号から保存している。
		fprintf(fp, "%d,"  , key.second);
		fprintf(fp, "%s,"  , key.first.c_str());
		fprintf(fp, "%d,"  , value.GetScore());
		fprintf(fp, "%d,\n", value.GetMaxCombo());
	}
	
	fclose(fp);

	return true;
}

CScore & CScoreManager::GetScore(const ScoreKey & key)
{
	return CScoreManager::GetManager().m_ScoreMap[key];
}

int CScoreManager::GetScoreValue(const ScoreKey & key)
{
	return CScoreManager::GetScore(key).GetScore();
}
