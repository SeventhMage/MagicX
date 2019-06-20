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
		class IVertexArrayObject;
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

			virtual IVertexArrayObject *GetVertexArrayObject() = 0;

			virtual IShaderProgram *GetShaderProgram() = 0;

			virtual void SetShaderProgram(IShaderProgram *program) = 0;
			virtual void SetUniform(const char *name, const void *value) = 0;
			virtual void SetUniform(int location, const void *value, uint size) = 0;
			//��������
			virtual void SetTexture(int slot, ITexture *pTexture) = 0;

			//�ύ���ݵ���Ⱦ����
			virtual void SumbitToRenderQueue() = 0;
			virtual void RemoveFromeRenderQueue() = 0;

			//�󶨵�ǰ����, ʹ��Ⱦ����֪�����ڴ������˭
			virtual void Bind() = 0;
			//���
			virtual void UnBind() = 0;

			//��Ⱦ����
			virtual void Enable(RenderAttribute attr) = 0;
			virtual void Disable(RenderAttribute attr) = 0;
			virtual bool IsEnabled(RenderAttribute attr) = 0;
		};
	}
}

#endif