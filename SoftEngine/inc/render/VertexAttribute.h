#ifndef _RENDER_VERTEX_ATTIBUTE_H_
#define _RENDER_VERTEX_ATTIBUTE_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		enum EVertexAttribute
		{
			VA_POSITION = 0,
			VA_TEXCOORD,
			VA_COLOR,
			VA_NORMAL,

			VA_COUNT,
		};

		typedef struct SVertexAttibute
		{
			EVertexAttribute attribute;	//��������
			uint count;					//����Ԫ�ظ���
			uint offset;				//��ʼλ��		
		}VertexAttrbute;

		typedef std::map<EVertexAttribute, VertexAttrbute> VertexFormat;


		typedef struct SVertexData
		{
			VertexFormat vertexFormat;					//�������Ը�ʽ
			uint count;									//��������
			uint stride;								//ÿ��stride������������ѭ��
			uint size;									//���ݳߴ�
			ubyte *pVertexData;

		}VertexData;

		typedef struct SIndexAttribute
		{
			EVertexAttribute attribute;
			uint offset;
		}IndexAttribute;

		typedef std::map<EVertexAttribute, IndexAttribute> IndexFormat;

		typedef struct SIndexData
		{
			IndexFormat format;						//������ʽ
			uint count;								//������
			uint size;
			ubyte *pIndexData;
		}IndexData;
	}
}

#endif