#ifndef _RENDER_E_UNIFORM_H_
#define _RENDER_E_UNIFORM_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		enum EUniformName
		{			
			UN_WORLD_MAT = 0,
			UN_VIEW_MAT,
			UN_PROJ_MAT,
			UN_LIGHT_POS,		//光源位置	
			UN_COLOR,
			UN_TEXTURE_0,
			UN_TEXTURE_1,
			UN_TEXTURE_2,
			UN_TEXTURE_3,

			UN_COUNT,
		};

		static struct
		{
			EUniformName identifer;
			char *name;
		}UniformName[UN_COUNT] = {			
			UN_WORLD_MAT, "worldMatrix",
			UN_VIEW_MAT, "viewMatrix",
			UN_PROJ_MAT, "projMatrix",
		};


		enum UniformFormat
		{
			UF_UNKNOWN,
			UF_INT,
			UF_FLOAT,
			UF_VEC2,
			UF_VEC3,
			UF_VEC4,
			UF_MAT3,
			UF_MAT4,
			UF_TEXTURE,
		};
	}
}

#endif