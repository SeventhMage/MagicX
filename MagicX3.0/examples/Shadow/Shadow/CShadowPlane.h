#ifndef _C_SHADOW_PLANE_H_
#define _C_SHADOW_PLANE_H_

#include "mx.h"

using namespace mx;

class CShadowPlane : public CEntity
{
public:
	CShadowPlane();
	~CShadowPlane();

	virtual void UpdateImp(int delta);

	void Create();
private:
	IRenderObject *m_pRenderObject;
	IRenderable *m_pRenderable;	
};

#endif