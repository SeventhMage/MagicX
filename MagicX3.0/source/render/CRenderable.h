/************************************************************************/
/* ��С��Ⱦʵ��ʵ��                                                     */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDERABLE_H_
#define _MX_RENDER_C_RENDERABLE_H_

#include "render/IRenderable.h"
#include "render/ITexture.h"
#include "render/IShaderProgram.h"
#include "render/IRenderList.h"

namespace mx
{
	namespace render
	{
		class CRenderable : public IRenderable
		{
		public:
			CRenderable(IRenderList *pRenderList);
			virtual ~CRenderable();

			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage);

			virtual IBufferObject *GetVertexBufferObject() { return m_pVBO; }
			virtual IBufferObject *GetIndexBufferObject() { return m_pIBO; }

			virtual void SetTexture(int slot, ITexture *pTexture);

			virtual void SetActive(bool bActive) { m_bActive = bActive; }
			virtual bool IsActive() { return m_bActive; }

			virtual void SumbitToRenderList();
			virtual void RemoveFromRenderList();
			virtual void Bind();
			virtual void UnBind();
		private:
			IRenderList *m_pRenderList;					//��Ⱦ�б�
			IBufferObject *m_pVBO;						//���㻺��������
			IBufferObject *m_pIBO;						//��������������

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//����
			bool m_bActive;
		};
	}
}

#endif