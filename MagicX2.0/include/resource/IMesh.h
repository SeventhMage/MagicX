#ifndef _MX_RESOURCE_IMESH_H_
#define _MX_RESOURCE_IMESH_H_

#include "core/CMatrix4.h"
#include "core/CVector3.h"
#include "core/CBoundingBox.h"
#include "IResource.h"
#include "mxType.h"

namespace mx
{
	namespace resource
	{
		using core::CMatrix4;
		using core::CVector3;
		using core::CBoundingBox;

		typedef struct STriangle
		{
			uint state;	//状态信息
			uint attr;	//物理属性
			uint color;	//颜色

			CVector3 *vList;	//顶点列表
			uint indices[3];		//索引
		}Triangle, *PTriangle;

		class IMesh : public IResource
		{
		public:
			virtual ~IMesh(){}
			virtual void rotateXZBy(double radians, const CVector3 &center = CVector3(0, 1.0f, 0)) = 0;
			virtual void rotateXYBy(double radians, const CVector3 &center = CVector3(0, 0, 1.0f)) = 0;
			virtual void rotateYZBy(double radians, const CVector3 &center = CVector3(1.0f, 0, 0)) = 0;

			virtual const CVector3 &GetWorldPosition() const = 0;
			virtual const float GetMaxRadius() const = 0;

			virtual Triangle *GetTrianglesList() const = 0;
			virtual CVector3 *GetVertices() const = 0;
			virtual uint GetVerticesNum() const = 0;
			virtual uint GetTrianglesNum() const = 0;			
		};
	}
}

#endif