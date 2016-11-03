/************************************************************************/
/* 网络数据接口                                                         */
/************************************************************************/

#ifndef _MX_RESOURCE_I_MESH_H_
#define _MX_RESOURCE_I_MESH_H_

#include "IResource.h"
#include "math/CVector2.h"
#include "math/CVector3.h"

namespace mx
{
	namespace resource
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
		class IMesh : public IResource
		{
		public:			
			virtual ~IMesh(){}

			//是否有索引，用于渲染器判断是否创建索引缓存
			virtual bool HaveIndex() = 0;
			virtual PTriangle GetMesh() = 0;
			virtual int GetStride() = 0;
		};
	}
}

#endif