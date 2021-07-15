#pragma once
#include "Mof.h"
#include <unordered_map>
#include <map>

class CScore
{
private:

	int m_Score;

	int m_MaxCombo;

public:

	CScore(void);

	~CScore(void);

	int GetScore(void) const;

	int GetMaxCombo(void) const;

	CScore& SetScore(const int& score);

	CScore& SetMaxCombo(const int& maxCombo);

	CScore& AddScore(const int& add);
};

using ScoreKey = std::pair<std::string, int>;

class CScoreManager
{
private:

	std::map<ScoreKey, CScore> m_ScoreMap;

public:

	~CScoreManager(void);

	static CScoreManager& GetManager(void);

	static bool Load(LPCMofChar pName);

	static bool Save(LPCMofChar pName);

	static CScore& GetScore(const ScoreKey& key);

	static int GetScoreValue(const ScoreKey& key);

private:

	CScoreManager(void);

};

