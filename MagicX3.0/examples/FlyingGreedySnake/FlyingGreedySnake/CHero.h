/************************************************************************/
/* Ö÷½Ç                                                                 */
/************************************************************************/

#ifndef _C_HERO_H_
#define _C_HERO_H_

#include "CPlayer.h"

class CHero : public CPlayer
{
public:
	CHero();
	virtual ~CHero();

	virtual void Update(int delta);

	void LeftRotate();
	void RightRotate();	
};

#endif