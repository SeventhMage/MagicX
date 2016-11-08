/************************************************************************/
/* ÿ��renderable�洢�˶���Ⱦ����һ���ύ                               */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERABLE_H_
#define _MX_RENDER_I_RENDERABLE_H_

#include "IBufferObject.h"
#include "ERender.h"
#include "IShaderProgram.h"
#include "ITexture.h"

namespace mx
{
	namespace render
	{
		class IRenderable
		{
		public:
			virtual ~IRenderable(){}
		
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage) = 0;

			virtual IBufferObject *GetVertexBufferObject() = 0;
			virtual IBufferObject *GetIndexBufferObject() = 0;

			//��������
			virtual void SetTexture(int slot, ITexture *pTexture) = 0;

			//��Ծ�Ĳ��ܱ���Ⱦ
			virtual void SetActive(bool bActive) = 0;
			virtual bool IsActive() = 0;

			//�ύ���ݵ���Ⱦ����
			virtual void SumbitToRenderList() = 0;
			virtual void RemoveFromRenderList() = 0;
			//�󶨵�ǰ����, ʹ��Ⱦ����֪�����ڴ������˭
			virtual void Bind() = 0;
			//���
			virtual void UnBind() = 0;
		};
	}
}

#endif