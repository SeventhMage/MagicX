/************************************************************************/
/* 索引缓冲区对象                                                       */
/************************************************************************/

#ifndef _MX_COPENGL_INDEX_BUFFER_OBJECT_H_
#define _MX_COPENGL_INDEX_BUFFER_OBJECT_H_

#include "render/IBufferObject.h"
#include "render/ERender.h"
#include "mxType.h"

namespace mx
{
	namespace render
	{
		class COpenGLIndexBufferObject : public IBufferObject
		{
		public:
			COpenGLIndexBufferObject(void *indices, GLsizei idsCount, GLenum idsType, GLenum mode, GLenum usage);
			virtual ~COpenGLIndexBufferObject();

			virtual void Bind();
			virtual void UnBind();

			virtual void BufferData(void *indices, int idsSize);
			virtual void BufferSubData(void *data, int size, int offset);
			virtual uint GetHandle() { return m_IBO; }
			virtual uint GetHandle() const { return m_IBO; }

			//GPUBufferType GetBufferType(){ return GBT_INDEX; };
			GLenum GetGPUBufferMode() { return m_gpuBufferMode; }
			GLenum GetGPUBufferUsage() { return m_gpuBufferUsage; }
			int GetIndicesNum() { return m_uIndicesNum; }						
			GLenum GetIndexType() { return m_idsType; }
		private:
			uint m_IBO;
			GLenum m_gpuBufferMode;
			GLenum m_gpuBufferUsage;
			GLenum m_idsType;
			GLsizei m_uIndicesNum;
		};
	}
}

#endif