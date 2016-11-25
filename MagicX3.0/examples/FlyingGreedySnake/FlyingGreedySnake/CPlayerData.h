/************************************************************************/
/* Íæ¼ÒÊý¾Ý                                                             */
/************************************************************************/

#ifndef _C_PLAYER_DATA_H_
#define _C_PLAYER_DATA_H_

class CPlayerData
{
public:
	CPlayerData();
	~CPlayerData();

	void AddLevel() { m_iLevel += 1; }
	void AddKill() { m_iKill += 1; }

	int GetLevel() { return m_iLevel; }
	int GetKill() { return m_iKill; }
private:
	int m_iLevel;
	int m_iKill;
	//int m_iDeath;
};

#endif