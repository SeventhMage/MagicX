/************************************************************************/
/* �������ݽӿ�                                                         */
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
		class IMesh : public IResource
		{
		public:			
			virtual ~IMesh(){}

			//�Ƿ���������������Ⱦ���ж��Ƿ񴴽���������
			virtual bool HaveIndex() = 0;
			virtual PTriangle GetMesh() = 0;
			virtual int GetStride() = 0;
		};
	}
}

#endif