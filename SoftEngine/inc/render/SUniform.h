#ifndef _RENDER_E_UNIFORM_H_
#define _RENDER_E_UNIFORM_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		enum EUniformName
		{
			UN_MODEL_MAT = 0,
			UN_WORLD_MAT,
			UN_VIEW_MAT,
			UN_PROJ_MAT,
			UN_CAM_POS,

			UN_COUNT,
		};

		struct
		{
			EUniformName identifer;
			char *name;
		}UniformName[UN_COUNT] = {
			UN_MODEL_MAT, "modelMatrix",
			UN_WORLD_MAT, "worldMatrix",
			UN_VIEW_MAT, "viewMatrix",
			UN_PROJ_MAT, "projMatrix",
		};


		enum EUniform
		{
			U_MAT,
		};

		typedef struct SUniform
		{
			char name[64];
			EUniform type;
			int size;
			ubyte *data;
		}Uniform;

	}
}

#endif