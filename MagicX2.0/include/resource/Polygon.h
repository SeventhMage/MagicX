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
			int state;	//״̬��Ϣ
			int attr;	//��������
			int color;	//��ɫ

			CVector3 *vList;	//�����б�
			int indices[3];		//����
		}Polygon, *PPolygon;

		typedef struct SPolygonFace
		{
			int state;		//״̬��Ϣ
			int attr;		//��������
			int color;		//��ɫ

			CVector3 vList[3];	//�����ζ���
			CVector3 tvList[3];	//�任��Ķ���

			struct SPolygonFace *next;	//ָ���б�����һ������ε�ָ��
			struct SPolygonFace *prev;	//ָ���б�����һ������ε�ָ��
		}PolygonF, *PPolygonF;

		typedef struct SObject
		{
			int id;
			char name[64];
			int state;
			int attr;
			float avgRadius;		//����ƽ���뾶
			float maxRadius;		//�������뾶

			CVector3 worldPos;		//������λ��
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
			int state;				//��Ⱦ�б��״̬
			int attr;				//��Ⱦ�б������
			PPolygonF polyPtrs[RENDERLIST_MAX_POLYS];
			Polygon	polyData[RENDERLIST_MAX_POLYS];
			int polysNum;
		}RenderList, *PRenderList;		
	}
}

#endif