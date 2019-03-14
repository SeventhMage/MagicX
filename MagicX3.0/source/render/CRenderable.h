/************************************************************************/
/* 最小渲染实体实现                                                     */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDERABLE_H_
#define _MX_RENDER_C_RENDERABLE_H_

#include "render/IRenderable.h"
#include "render/ITexture.h"
#include "render/IShaderProgram.h"
#include "render/IRenderList.h"
#include "render/IRenderer.h"
#include "mxDef.h"

#include <map>

namespace mx
{
	namespace render
	{
		class CRenderable : public IRenderable
		{
		public:
			struct Uniform
			{
				char m_name[MAX_FILE_NAME];
				int m_location;
				UniformFormat m_format;
				int m_count;
				int m_size;
				byte *m_value;
				bool m_bDirty;
				Uniform()
					: m_location(0)
					, m_format(UF_UNKNOWN)
					, m_count(0)
					, m_size(0)
					, m_value(NULL)
					, m_bDirty(false)
				{
					memset(m_name, 0, sizeof(m_name));
				}
				~Uniform()
				{
					SAFE_DEL(m_value);
				}

				void SetValue(const void *value, uint size)
				{
					if (value && size > 0)
					{
						if (!m_value || size != m_size)
						{
							m_size = size;
							SAFE_DEL(m_value);
							m_value = new byte[m_size];
						}
						memcpy(m_value, value, m_size);
						Dirty(true);
					}
				}
				inline void Dirty(bool bDirty) { m_bDirty = bDirty; }
				inline bool IsDirty() const { return m_bDirty; }
			private:
				Uniform(const Uniform&);
				Uniform &operator=(const Uniform &);
			};
			typedef std::map<int, Uniform> UniformArray;

			CRenderable(IRenderList *pRenderList, IRenderer *pRenderer);
			CRenderable(IRenderQueue *pQueue, IRenderer *pRenderer);
			virtual ~CRenderable();

			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage);

			virtual IBufferObject *GetVertexBufferObject() { return m_pVBO; }
			virtual IBufferObject *GetIndexBufferObject() { return m_pIBO; }

			virtual IVertexArrayObject *GetVertexArrayObject() { return m_pVAO; }

			virtual IShaderProgram *GetShaderProgram() { return m_pShaderProgram; }
			virtual void SetShaderProgram(IShaderProgram *program);
			
			virtual void SetUniform(const char *name, void *value);
			virtual void SetUniform(int location, void *value, uint size);

			virtual void SetTexture(int slot, ITexture *pTexture);

			virtual void SumbitToRenderList();
			virtual void RemoveFromRenderList();
			virtual void SumbitToRenderQueue();
			virtual void Bind();
			virtual void UnBind();
			virtual void Enable(RenderAttribute attr) { m_bRenderAttrs[attr] = true; }
			virtual void Disable(RenderAttribute attr) { m_bRenderAttrs[attr] = false; }
			virtual bool IsEnabled(RenderAttribute attr) { return m_bRenderAttrs[attr]; }
		private:
			IShaderProgram *m_pShaderProgram;			//shader程序
			UniformArray m_uniforms;
			IRenderList *m_pRenderList;					//渲染列表
			IRenderQueue *m_pRenderQueue;
			IVertexArrayObject *m_pVAO;
			IBufferObject *m_pVBO;						//顶点缓冲区对象
			IBufferObject *m_pIBO;						//索引缓冲区对象

			bool m_bRenderAttrs[RA_NUM];				//渲染属性

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//纹理

			IRenderer *m_pRenderer;
		};
	}
}

#endif