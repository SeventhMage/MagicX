/************************************************************************/
/* ��С��Ⱦʵ��ʵ��                                                     */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDERABLE_H_
#define _MX_RENDER_C_RENDERABLE_H_

#include "render/IRenderable.h"
#include "render/ITexture.h"
#include "render/IShaderProgram.h"
#include "render/IRenderList.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace render
	{
		class CRenderable : public IRenderable
		{
		public:
			CRenderable(IRenderList *pRenderList, IRenderer *pRenderer);
			virtual ~CRenderable();

			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage);

			virtual IBufferObject *GetVertexBufferObject() { return m_pVBO; }
			virtual IBufferObject *GetIndexBufferObject() { return m_pIBO; }

			virtual IShaderProgram *GetShaderProgram() { return m_pShaderProgram; }
			virtual void SetShaderProgram(IShaderProgram *program);

			virtual void SetTexture(int slot, ITexture *pTexture);

			virtual void SumbitToRenderList();
			virtual void RemoveFromRenderList();
			virtual void Bind();
			virtual void UnBind();
			virtual void Enable(RenderAttribute attr) { m_bRenderAttrs[attr] = true; }
			virtual void Disable(RenderAttribute attr) { m_bRenderAttrs[attr] = false; }
			virtual bool IsEnabled(RenderAttribute attr) { return m_bRenderAttrs[attr]; }
		private:
			IShaderProgram *m_pShaderProgram;			//shader����
			IRenderList *m_pRenderList;					//��Ⱦ�б�
			IBufferObject *m_pVBO;						//���㻺��������
			IBufferObject *m_pIBO;						//��������������

			bool m_bRenderAttrs[RA_NUM];				//��Ⱦ����

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//����

			IRenderer *m_pRenderer;
		};
	}
}

#endif