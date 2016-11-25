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

	virtual void SetPosition(const CVector3 &pos);
	virtual const CVector3 &GetPosition();

	void Create();
	void Increase();

	CSphereEntity *GetHead(){ return m_pHead; }

protected:
	//等级半径转化
	float GetHeadRadius();
	float GetBodyRadius();

	//等级与切片转化
	int GetSlice();
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