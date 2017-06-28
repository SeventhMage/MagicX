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
			EVertexAttribute attribute;	//顶点属性
			uint count;					//属性元素个数
			uint offset;				//开始位置		
		}VertexAttrbute;

		typedef std::vector<VertexAttrbute> VertexFormat;


		typedef struct SVertexData
		{
			VertexFormat vertexFormat;					//顶点属性格式
			uint count;									//顶点数量
			uint stride;								//每隔stride顶点属性数量循环
			uint size;									//数据尺寸
			ubyte *vertexData;

		}VertexData;
	}
}

#endif