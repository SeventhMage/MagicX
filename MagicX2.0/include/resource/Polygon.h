#ifndef _MX_RENDER_POLYGON_H_
#define _MX_RENDER_POLYGON_H_

#include "core/CVector3.h"

namespace mx
{
	namespace resource
	{
		using namespace mx::core;
		typedef struct SPolyon
		{
			int state;	//状态信息
			int attr;	//物理属性
			int color;	//颜色

			CVector3 *vList;	//顶点列表
			int indices[3];		//索引
		}Polygon, *PPolygon;

		typedef struct SPolygonFace
		{
			int state;		//状态信息
			int attr;		//物理属性
			int color;		//颜色

			CVector3 vList[3];	//三角形顶点
			CVector3 tvList[3];	//变换后的顶点

			struct SPolygonFace *next;	//指向列表中下一个多边形的指针
			struct SPolygonFace *prev;	//指向列表中上一个多边形的指针
		}PolygonF, *PPolygonF;

		typedef struct SObject
		{
			int id;
			char name[64];
			int state;
			int attr;
			float avgRadius;		//物体平均半径
			float maxRadius;		//物体最大半径

			CVector3 worldPos;		//世界中位置
			CVector3 dir;
			CVector3 ux, uy, uz;

			int verticesNum;
			CVector3 *pvLocalList;
			CVector3 *pvTransList;

			int polysNum;
			Polygon *pPolysList;
		}Object, *PObject;


#define RENDERLIST_MAX_POLYS 128
		typedef struct SRenderList
		{
			int state;				//渲染列表的状态
			int attr;				//渲染列表的属性
			PPolygonF polyPtrs[RENDERLIST_MAX_POLYS];
			Polygon	polyData[RENDERLIST_MAX_POLYS];
			int polysNum;
		}RenderList, *PRenderList;		
	}
}

#endif