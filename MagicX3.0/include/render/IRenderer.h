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
#include "IMaterial.h"
#include "IShaderProgram.h"
#include "IShadowMap.h"
#include "IRenderTargetManager.h"
#include "renderphase/IRenderPhaseManager.h"
#include "IMaterialManager.h"
#include "IRenderQueue.h"
#include "IScreenAlignedQuadManager.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};


			virtual void Initialize(int width, int height) = 0;

			//��ȡ��Ⱦ����������
			virtual IRenderDriver *GetRenderDriver() = 0;

			//��ʼ��Ⱦ������
			virtual void BeginRender() = 0;
			virtual void Render() = 0;
			//�����Ⱦ�б�
			virtual void EndRender() = 0;

			//��Ⱦ����
			virtual void Render(IRenderable *pRenderable) = 0;

			//������Ⱦʵ��
			virtual IRenderable *CreateRenderable(IRenderList *pObject) = 0;
			virtual IRenderable *CreateRenderable(IRenderQueue *pQueue) = 0;

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
			virtual ITexture *CreateCubeTexture(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back) = 0;
			virtual void DestroyTexture(ITexture *pTexture) = 0;

			//ShaderProgram
			virtual IShaderProgram *CreateShaderProgram() = 0;
			virtual void DestroyShaderProgram(IShaderProgram *pShaderProgram) = 0;

			virtual int GetTriangleNum() = 0;


			//manager
			virtual IRenderTargetManager *GetRenderTargetManager() const = 0;
			virtual IRenderPhaseManager *GetRenderPhaseManager() const = 0;
			virtual void ProcessRenderPhase() const = 0;
			virtual IMaterialManager *GetMaterialManager() const = 0;

			virtual IScreenAlignedQuadManager *GetScreenAlignedQuadManager() const = 0;
			virtual void SubmitScreenAlignedQuad() const = 0;

		private:
			
		};
	}
}

#endif