/************************************************************************/
/* µÿ√Ê                                                                 */
/************************************************************************/


#ifndef _C_GGROUND_H_
#define _C_GGROUND_H_

#include "mx.h"

using namespace mx;

class CGround : public CEntity
{
public:
	CGround();
	~CGround();

	virtual void UpdateImp(int delta);

	void Create();
private:
	IRenderObject *m_pRenderObject;
	IRenderable *m_pRenderable;
};

#endif