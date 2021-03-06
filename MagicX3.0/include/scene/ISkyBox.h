/************************************************************************/
/* ��պнӿ�                                                           */
/************************************************************************/

#ifndef _MX_SCENE_I_SKYBOX_H_
#define _MX_SCENE_I_SKYBOX_H_

#include "render/ITexture.h"

namespace mx
{
	namespace scene
	{
		class ISkyBox
		{
		public:
			virtual ~ISkyBox(){}
			virtual bool Create(const char *filename) = 0;
			virtual bool Create(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back) = 0;
			virtual render::ITexture *GetTexture() = 0;
			virtual const CMatrix4 &GetModelMatrix() = 0;
		};
	}
}

#endif