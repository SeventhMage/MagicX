/************************************************************************/
/* 玩家                                                                 */
/************************************************************************/
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include "CGameUnit.h"
#include "CPlayerData.h"

#include <vector>
#include <list>

class CPlayer : public CGameUnit
{
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void SetPosition(const CVector3 &pos);
	virtual const CVector3 &GetPosition();
	virtual void Update(int delta);

	void Create();
	void Increase();
	void UpdatePosition();

	CSphereEntity *GetHead(){ return m_pHead; }

protected:
	//等级半径转化
	float GetHeadRadius();
	float GetBodyRadius();

	//等级与切片转化
	int GetSlice();
	//初始化位置
	void InitPosition();

private:
	CSphereEntity *m_pHead;	
	std::list<CSphereEntity *>m_listBody;
	CSphereEntity *m_pTail;
	

	CReflectObject *m_pReflectObject;
	CColorPointLightObject *m_pColorLightObject;

	CPlayerData m_playerData;

	CVector3 m_vHeadPosRecord;
	std::vector<CVector3>m_vecBodyPosRecord;

};

#endif