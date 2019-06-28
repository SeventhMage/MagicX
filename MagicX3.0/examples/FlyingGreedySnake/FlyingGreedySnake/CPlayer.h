/************************************************************************/
/* ���                                                                 */
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

	virtual void InitConfigTable();
	virtual void SetPosition(const CVector3 &pos);
	virtual void Update(int delta);
	virtual void SetLevel(int level);
	virtual void Release();

	void Increase(const CVector3 &color);
	void UpdatePosition();

	CSphereEntity *GetHead(){ return m_pHead; }

protected:
	//�ȼ��뾶ת��
	float GetHeadRadius();
	float GetBodyRadius();

	//�ȼ�����Ƭת��
	int GetSlice();
	//��ʼ��λ��
	void InitPosition();

	void Create();
private:
	CSphereEntity *m_pHead;	
	std::list<CSphereEntity *>m_listBody;
	CSphereEntity *m_pTail;

	CPlayerData m_playerData;

	CVector3 m_vHeadPosRecord;
	std::vector<CVector3>m_vecBodyPosRecord;
	

	float m_fVolume;

};

#endif