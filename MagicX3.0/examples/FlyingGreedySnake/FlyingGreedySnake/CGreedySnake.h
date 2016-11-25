/************************************************************************/
/* Ö÷¿ØÖÆ³ÌÐò                                                           */
/************************************************************************/

#ifndef _C_GREEDY_SNAKE_H_
#define _C_GREEDY_SNAKE_H_

#include "mx.h"
#include "CGameScene.h"

using namespace mx;

class CGreedySnake : public CSingleton<CGreedySnake>
{
public:
	friend class CSingleton<CGreedySnake>;
	
	void InitGame(int width, int height, bool fullscreen);
	void Run();

	bool Update(int delta);
private:
	CGreedySnake();
	~CGreedySnake();

	CGameScene *m_pGameScene;
};

#endif