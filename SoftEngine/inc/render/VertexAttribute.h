#ifndef _RENDER_VERTEX_ATTIBUTE_H_
#define _RENDER_VERTEX_ATTIBUTE_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		enum EVertexAttribute
		{
			VA_POSITION = 1,
			VA_COLOR = 1 << 2,
			VA_TEXCOORD = 1 << 3,
			VA_NORMAL = 1 << 4,			
		};

		typedef struct SVertexAttibute
		{
			EVertexAttribute attribute;	//��������
			uint count;					//����Ԫ�ظ���
			uint offset;				//��ʼλ��		
		}VertexAttrbute;

		typedef std::vector<VertexAttrbute> VertexFormat;


		typedef struct SVertices
		{
			VertexFormat format;						//�������Ը�ʽ
			uint count;									//��������
			uint stride;								//ÿ��stride������������ѭ��
			uint size;									//���ݳߴ�
			float *pVertexData;

		}Vertices;
	}
}

#endif