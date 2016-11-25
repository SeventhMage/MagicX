/************************************************************************/
/* 游戏场景                                                             */
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
	//std::vector<CPlayer *> m_vecPlayer;		//场景中的所有玩家
	std::vector<CNPC *>m_vecNPC;			//场景中的所有npc
	CHero *m_pHero;							//主角
};

#endif