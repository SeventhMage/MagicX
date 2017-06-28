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
			VA_TEXCOORD = 2,
			VA_COLOR = 4,
			VA_NORMAL = 8,
		};

		typedef struct SVertexAttibute
		{
			EVertexAttribute attribute;	//��������
			uint count;					//����Ԫ�ظ���
			uint offset;				//��ʼλ��		
		}VertexAttrbute;

		typedef std::vector<VertexAttrbute> VertexFormat;


		typedef struct SVertexData
		{
			VertexFormat vertexFormat;					//�������Ը�ʽ
			uint count;									//��������
			uint stride;								//ÿ��stride������������ѭ��
			uint size;									//���ݳߴ�
			ubyte *vertexData;

		}VertexData;
	}
}

#endif