/************************************************************************/
/* 玩家                                                                 */
/************************************************************************/
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include "CGameUnit.h"
#include "CPlayerData.h"

class CPlayer : public CGameUnit
{
public:
	CPlayer();
	virtual ~CPlayer();

	void Increase();

protected:
	//等级半径转化
	float GetRadius();
	//等级与切片转化
	float GetSlice();
	//初始化位置
	void InitPosition(CSphereEntity *entity);
private:
	CSphereEntity *m_pHead;	
	CSphereEntity *m_pBody;
	CSphereEntity *m_pTail;

	CReflectObject *m_pReflectObject;
	CColorPointLightObject *m_pColorLightObject;

	CPlayerData m_playerData;

};

#endif