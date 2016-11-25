/************************************************************************/
/* 游戏场景                                                             */
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
	//std::vector<CPlayer *> m_vecPlayer;		//场景中的所有玩家
	std::list<CNPC *>m_listNPC;					//场景中的所有npc
	CHero *m_pHero;								//主角
	IScene *m_pScene;
};

#endif