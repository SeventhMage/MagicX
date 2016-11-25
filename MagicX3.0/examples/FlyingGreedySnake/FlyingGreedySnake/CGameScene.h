/************************************************************************/
/* ��Ϸ����                                                             */
/************************************************************************/

#ifndef _C_GAME_SCENE_H_
#define _C_GAME_SCENE_H_

#include "CPlayer.h"
#include "CNPC.h"
#include "CHero.h"

#include <list>

class CGameScene
{
public:
	CGameScene();
	~CGameScene();

	void InitScene();
	void Update(int delta);
	CHero *GetHero() { return m_pHero; }
private:
	//std::vector<CPlayer *> m_vecPlayer;		//�����е��������
	std::list<CNPC *>m_listNPC;					//�����е�����npc
	CHero *m_pHero;								//����
	IScene *m_pScene;
};

#endif