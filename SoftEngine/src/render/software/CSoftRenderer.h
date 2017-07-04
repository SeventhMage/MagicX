#ifndef _SE_C_SOFT_RENDERER_H_
#define _SE_C_SOFT_RENDERER_H_

#include "render/IRenderer.h"
#include "render/IBuffer.h"
#include "CSoftRenderDriver.h"
#include "base/CSingleton.h"
#include "render/IRenderQueue.h"
#include "math/CMatrix4.h"
#include "render/SRenderMemory.h"
#include "../STriangleMesh.h"

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

			virtual void UpdateUniform(EUniformName name, ubyte *data, uint size);
			virtual void SubmitRenderCell(IRenderCell *pCell);

			virtual void Clear();
			virtual void Render();
			virtual void Render(uint materialId, uint bufferId, uint textureId);			
		private:			
			void TranslateWorldToCamera(TriangleList &triList);
			void TranslateCameraToScreen(TriangleList &triList);
			bool BackCulling(const Triangle &triangle);										//背面剔除
			bool TriangleSort(const Triangle &t1, const Triangle &t2);						//三角形排序函数
			void VertexLightCalc(TriangleList &triList);
			void LoadMaterial();
		private:
			CSoftRenderDriver *m_pSoftRD;
			RenderQueueGroup m_renderQueueGroup;
			std::map<int, IBuffer *> m_mapCPUBuffer;
			math::CMatrix4 m_worldMatrix;
			math::CMatrix4 m_viewMatrix;
			math::CMatrix4 m_projMatrix;
			math::CMatrix4 m_normalMatrix;		
			math::CVector3 m_cameraPos;
		};
	}
}

#endif