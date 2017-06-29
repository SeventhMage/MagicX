#ifndef _SE_C_SOFT_RENDERER_H_
#define _SE_C_SOFT_RENDERER_H_

#include "render/IRenderer.h"
#include "render/IBuffer.h"
#include "CSoftRenderDriver.h"
#include "base/CSingleton.h"
#include "render/IRenderQueue.h"
#include "math/CMatrix4.h"

namespace se
{
	namespace render
	{
		class CSoftRenderer : public IRenderer, public base::CSingleton<CSoftRenderer>
		{
		public:
			CSoftRenderer();
			virtual ~CSoftRenderer();

			virtual IRenderDriver *GetRenderDriver() { return m_pSoftRD; }	
			virtual RenderDriverType GetRenderDriverType() { m_pSoftRD->GetDriverType(); }

			virtual uint CreateBuffer();
			virtual void DestroyBuffer(uint bufferId);
			virtual void BufferData(uint bufferId,
				ubyte *vertices,						//顶点数据				
				uint vertSize,							//顶点数据尺寸
				int count,								//顶点数量
				VertexFormat format,					//顶点属性格式
				ubyte *indices,							//索引数据
				uint indicesSize						//索引数据尺寸
				) = 0;

			virtual void UpdateUniform(EUniform type, EUniformName name, ubyte *data, uint size);
			virtual void SubmitRenderCell(IRenderCell *pCell);

			virtual void Clear();
			virtual void Render();
			virtual void Render(uint materialId, uint bufferId, uint textureId);

			virtual void SetRenderMemory(ubyte *addr){ m_renderAddr = addr; }
		private:
			void LoadMaterial();
		private:
			CSoftRenderDriver *m_pSoftRD;
			RenderQueueGroup m_renderQueueGroup;
			std::map<int, IBuffer *> m_mapCPUBuffer;
			math::CMatrix4 m_modelMatrix;
			math::CMatrix4 m_viewMatrix;
			math::CMatrix4 m_projMatrix;
			ubyte *m_renderAddr;
		};
	}
}

#endif