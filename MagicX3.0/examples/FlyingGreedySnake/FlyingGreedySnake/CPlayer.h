/************************************************************************/
/* ���                                                                 */
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
	//�ȼ��뾶ת��
	float GetRadius();
	//�ȼ�����Ƭת��
	float GetSlice();
	//��ʼ��λ��
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