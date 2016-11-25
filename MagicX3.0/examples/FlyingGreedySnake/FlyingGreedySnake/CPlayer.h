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

	virtual void SetPosition(const CVector3 &pos);
	virtual const CVector3 &GetPosition();

	void Create();
	void Increase();

	CSphereEntity *GetHead(){ return m_pHead; }

protected:
	//�ȼ��뾶ת��
	float GetHeadRadius();
	float GetBodyRadius();

	//�ȼ�����Ƭת��
	int GetSlice();
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