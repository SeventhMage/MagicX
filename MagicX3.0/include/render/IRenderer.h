/************************************************************************/
/* 渲染器接口                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERER_H_
#define _MX_RENDER_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IBufferData.h"
#include "IRenderable.h"
#include "IVertexArrayObject.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};

			//获取渲染器驱动程序
			virtual IRenderDriver *GetRenderDriver() = 0;

			//渲染对象
			virtual void Render(IRenderable *pRenderable) = 0;
			//渲染
			virtual void Render() = 0;

			//创建渲染实体
			virtual IRenderable *CreateRenderable(IVertexArrayObject *pObject) = 0;
			//销毁渲染实体
			virtual void DestroyRenderable(IRenderable *pRenderable) = 0;

			//创建缓冲区对象
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage) = 0;

			//销毁缓冲区对象
			virtual void DestroyBufferObject(IBufferObject *object) = 0;

			//创建shader程序
			virtual IShaderProgram *CreateShaderProgram() = 0;
			virtual void DestroyShaderProgram(IShaderProgram *pProgram) = 0;

			//创建顶点数组对象
			virtual IVertexArrayObject *CreateVertexArrayObject() = 0;
			virtual void DestroyVertexArrayObject(IVertexArrayObject *pObject) = 0;
		};
	}
}

#endif