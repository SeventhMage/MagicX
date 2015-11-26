#ifndef _H_MESH_H_INC_
#define _H_MESH_H_INC_

#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		typedef struct
		{
			CVector3 vPosition;
			CVector3 vNormal;
			float u, v;
		}SVertex;

		class IMesh
		{
		public:
			IMesh(){}
			virtual ~IMesh(){}
		};
	}
}

#endif