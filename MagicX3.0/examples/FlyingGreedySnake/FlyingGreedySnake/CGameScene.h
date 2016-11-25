/************************************************************************/
/* ��Ϸ����                                                             */
/************************************************************************/

#ifndef _C_GAME_SCENE_H_
#define _C_GAME_SCENE_H_

#include "CPlayer.h"
#include "CNPC.h"
#include "CHero.h"

#include <vector>

class CGameScene
{
public:
	CGameScene();
	~CGameScene();

	void InitScene();

private:
	//std::vector<CPlayer *> m_vecPlayer;		//�����е��������
	std::vector<CNPC *>m_vecNPC;			//�����е�����npc
	CHero *m_pHero;							//����
};

#endif