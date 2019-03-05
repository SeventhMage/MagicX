/************************************************************************/
/* 渲染器接口                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERER_H_
#define _MX_RENDER_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IBufferData.h"
#include "IRenderable.h"
#include "IVertexArrayObject.h"
#include "ITexture.h"
#include "IMaterial.h"
#include "IShaderProgram.h"
#include "IShadowMap.h"
#include "IRenderTargetManager.h"

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

			//开始渲染清理工作
			virtual void BeginRender() = 0;
			virtual void Render() = 0;
			//清空渲染列表
			virtual void EndRender() = 0;

			//渲染对象
			virtual void Render(IRenderable *pRenderable) = 0;

			//创建渲染实体
			virtual IRenderable *CreateRenderable(IRenderList *pObject) = 0;
			//销毁渲染实体
			virtual void DestroyRenderable(IRenderable *pRenderable) = 0;

			//创建缓冲区对象
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage) = 0;

			//销毁缓冲区对象
			virtual void DestroyBufferObject(IBufferObject *object) = 0;

			//创建顶点数组对象
			virtual IVertexArrayObject *CreateVertexArrayObject() = 0;
			virtual void DestroyVertexArrayObject(IVertexArrayObject *pObject) = 0;

			//创建纹理
			virtual ITexture *CreateTexture(const char *filename) = 0;
			virtual ITexture *CreateCubeTexture(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back) = 0;
			virtual void DestroyTexture(ITexture *pTexture) = 0;

			//ShaderProgram
			virtual IShaderProgram *CreateShaderProgram() = 0;
			virtual void DestroyShaderProgram(IShaderProgram *pShaderProgram) = 0;

			//材质
			virtual IMaterial *CreateMaterial() = 0;
			virtual void DestroyMaterial(IMaterial *pMaterial) = 0;

			virtual IShadowMap *GetShadowMap() = 0;

			//阴影图渲染标志
			virtual void SetRenderShadowMap(bool rend) = 0;
			virtual bool IsRenderShadowMap() = 0;

			virtual IRenderTargetManager *GetRenderTargetManager() const = 0;
		private:
			
		};
	}
}

#endif