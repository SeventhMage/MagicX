#ifndef _BASE_VERTEX_ATTIBUTE_H_
#define _BASE_VERTEX_ATTIBUTE_H_

#include "base/seType.h"

namespace se
{
	namespace base
	{
		enum EVertexAttribute
		{
			VA_NONE = 0,
			VA_POSITION = 1,
			VA_COLOR = 1 << 2,
			VA_TEXCOORD = 1 << 3,
			VA_NORMAL = 1 << 4,			
		};

		typedef struct SVertexAttibute
		{
			SVertexAttibute()
			:attribute(VA_NONE), offset(0)
			{
			}
			SVertexAttibute(EVertexAttribute attr, uint offset)
			:attribute(attr), offset(offset)
			{
			}
			EVertexAttribute attribute;	//��������			
			uint offset;				//��ʼλ��		
		}VertexAttrbute;

		typedef std::vector<VertexAttrbute> VertexFormat;


		typedef struct SVertices
		{
			SVertices()
			:format(0), count(0), stride(0), size(0), pVertexData(nullptr)
			{
			}
			VertexFormat format;						//�������Ը�ʽ
			uint count;									//��������
			uint stride;								//ÿ��stride������������ѭ��
			uint size;									//���ݳߴ�
			ubyte *pVertexData;

		}Vertices;

		typedef struct SIndices
		{
			SIndices()
			: size(0), pIndexData(nullptr)
			{}			
			uint size;
			ushort *pIndexData;
		}Indices;
	}
}

#endif