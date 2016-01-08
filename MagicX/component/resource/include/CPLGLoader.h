#ifndef _MX_RESOURCE_C_PLG_LOADER_H_
#define _MX_RESOURCE_C_PLG_LOADER_H_

#include <stdio.h>

namespace mx
{
	namespace resource
	{
#define MAX_FILE_NAME 256

#define PLX_RGB_MASK	0x8000	//��ȡRGB/������ɫģʽ������
#define PLX_SHADER_MODE_MASK	0x6000	//��ȡ��ɫģʽ������
#define PLX_2SIDE_MASK	0x1000	//��ȡ˫��ģʽ������
#define PLX_COLOR_MASK	0x0fff	//RGBģʽxxxxrrrrggggbbbb; ��ɫ����ģʽxxxxxxxxxiiiiiiii

//�����ж���ɫģʽ�ı��
#define PLX_COLOR_MODE_RGB_FLAG	0x8000	//ʹ��RGB��ɫ
#define PLX_COLOR_MODE_INDEXED_FLAG	0x0000	//ʹ��8λ��ɫ����

//ҳ����
#define PLX_2SIDED_FLAG	0x1000	//˫���
#define PLX_1SIDED_FLAG	0x0000	//�����

//��ɫģʽ���
#define PLX_SHADER_MODE_PURE_FLAG 0x0000	//�̶���ɫ
#define PLX_SHADER_MODE_FLAT_FLAT	0x2000	//�㶨��ɫ
#define PLX_SHADER_MODE_GOURAUD_FLAG 0x4000	//gouraud��ɫ
#define PLX_SHADER_MODE_PHONE_FLAG	0x6000	//phone��ɫ

		typedef struct
		{
			float x, y, z;
		}Vertex;

		typedef struct
		{
			int attr;
			int VerticesNum;
			int *indices;
		}Polygon;

		typedef struct
		{
			char objectName[MAX_FILE_NAME];
			int verticesNum;
			int polygonsNum;
			Vertex *vertices;
			Polygon *polygons;
		}PLG;

		class CPLGLoader
		{
		public:
			CPLGLoader(const char *filename);
			~CPLGLoader();
			const char *GetObjectName();
			int GetVerticesNum();
			int GetPolygonsNum();
			Vertex *GetVertices();
			Polygon *GetPolygons();
		private:
			char *GetLinePLG(char *buffer, int maxlength, FILE *fp);
		private:
			char *filename[MAX_FILE_NAME];
			PLG m_plg;
		};
	}
}

#endif
