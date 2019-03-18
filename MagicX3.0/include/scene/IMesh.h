/************************************************************************/
/* 网络数据接口                                                         */
/************************************************************************/

#ifndef _MX_RESOURCE_I_MESH_H_
#define _MX_RESOURCE_I_MESH_H_

#include "math/CVector2.h"
#include "math/CVector3.h"
#include "math/CMatrix4.h"
#include "math/CRay.h"
#include "base/SColor.h"
#include "mxType.h"

namespace mx
{
	namespace scene
	{
		using namespace math;
		//顶点结构
		typedef struct SVertex
		{
			union
			{
				float m[8];
				struct
				{
					float x, y, z;			//位置信息
					float nx, ny, nz;		//法线
					float u, v;				//纹理坐标
				};
				struct
				{
					CVector3 position;		//位置
					CVector3 normal;		//法线
					CVector2 texcoord;		//纹理坐标
				};
			};
		}Vertex, *PVertex;

		//三角形
		typedef struct STriangle
		{
			Vertex v[3];
		}Triangle, *PTriangle;

		//网格数据
		class IMesh
		{
		public:			
			virtual ~IMesh(){}
			virtual bool Intersect(const math::CRay &ray, const math::CMatrix4 &transform, float *distance = nullptr, math::CVector3 *hitPoint = nullptr, math::CVector2 *uv = nullptr, uint *triIndex = nullptr) = 0;
			virtual void GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor) = 0;
		};
	}
}

#endif