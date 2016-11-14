/************************************************************************/
/* ��Ⱦ���ӿ�                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERER_H_
#define _MX_RENDER_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IBufferData.h"
#include "IRenderable.h"
#include "IVertexArrayObject.h"
#include "ITexture.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};

			//��ȡ��Ⱦ����������
			virtual IRenderDriver *GetRenderDriver() = 0;

			//��ʼ��Ⱦ������
			virtual void BeginRender() = 0;

			//��Ⱦ����
			virtual void Render(IRenderable *pRenderable) = 0;

			//������Ⱦʵ��
			virtual IRenderable *CreateRenderable(IRenderList *pObject) = 0;
			//������Ⱦʵ��
			virtual void DestroyRenderable(IRenderable *pRenderable) = 0;

			//��������������
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage) = 0;

			//���ٻ���������
			virtual void DestroyBufferObject(IBufferObject *object) = 0;

			//���������������
			virtual IVertexArrayObject *CreateVertexArrayObject() = 0;
			virtual void DestroyVertexArrayObject(IVertexArrayObject *pObject) = 0;

			//��������
			virtual ITexture *CreateTexture(const char *filename) = 0;
			virtual ITexture *CreateCubeTexture(const char *front, const char *back, const char *left,
				const char *right, const char *top, const char *bottom) = 0;
			virtual void DestroyTexture(ITexture *pTexture) = 0;
		};
	}
}

#endif