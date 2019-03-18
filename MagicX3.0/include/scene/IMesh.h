/************************************************************************/
/* �������ݽӿ�                                                         */
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
		//����ṹ
		typedef struct SVertex
		{
			union
			{
				float m[8];
				struct
				{
					float x, y, z;			//λ����Ϣ
					float nx, ny, nz;		//����
					float u, v;				//��������
				};
				struct
				{
					CVector3 position;		//λ��
					CVector3 normal;		//����
					CVector2 texcoord;		//��������
				};
			};
		}Vertex, *PVertex;

		//������
		typedef struct STriangle
		{
			Vertex v[3];
		}Triangle, *PTriangle;

		//��������
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