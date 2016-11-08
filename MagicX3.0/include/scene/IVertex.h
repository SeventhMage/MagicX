/************************************************************************/
/* 顶点格式，用户继承接口以创建数据                                     */
/************************************************************************/

#ifndef _MX_SCENE_S__VERTEX_H_
#define _MX_SCENE_S__VERTEX_H_

namespace mx
{
	namespace scene
	{
		//顶点格式属性
		enum EVertexAttribute
		{
			VF_POSITION					= 0x0001,		//位置
			VF_COLOR					= 0x0002,		//颜色
			VF_TEXCOORD					= 0x0004,		//纹理坐标
			VF_NORMAL					= 0x0008,		//法线

			VF_COMPLETE = VF_POSITION | VF_COLOR | VF_TEXCOORD | VF_NORMAL,
		};		

		class IVertex
		{		
		public:
			virtual~IVertex(){}

			//返回当前顶点格式
			virtual EVertexAttribute GetVertexAttribute() = 0;
			//返回顶点数据
			virtual void *GetVertexData() = 0;
			//返回顶点数量
			virtual uint GetVerticeCount() = 0;
			//返回顶点尺寸
			virtual uint GetVerticeSize() = 0;
			//返回索引数据
			virtual void *GetIndicesData() = 0;
			//返回索引数量
			virtual uint GetIndicesCount() = 0;
			//返回纹理坐标
			virtual void *GetTexCoordData() = 0;
			virtual uint GetTexCoordCount() = 0;
			virtual uint GetTexCoordSize() = 0;
		};

	}
}

#endif