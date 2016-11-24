/************************************************************************/
/* Ö÷¿ØÖÆ³ÌÐò                                                           */
/************************************************************************/

#ifndef _C_GREEDY_SNAKE_H_
#define _C_GREEDY_SNAKE_H_

#include "mx.h"

using namespace mx;

class CGreedySnake : public CSingleton<CGreedySnake>
{
public:
	friend class CSingleton<CGreedySnake>;
	

	void Update(int delta);
private:
	CGreedySnake(){}
	~CGreedySnake();
};

#endif