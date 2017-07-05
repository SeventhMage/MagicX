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
			virtual RenderDriverType GetRenderDriverType() { return m_pSoftRD->GetDriverType(); }
			virtual IRenderCell *CreateRenderCell(uint bufferId, uint materialId, uint textureId);
			virtual void DestroyRenderCell(IRenderCell *pCell);
			virtual uint CreateBuffer();
			virtual void DestroyBuffer(uint bufferId);			
			virtual void BufferData(uint bufferId, base::Vertices *pVertices, base::Indices *pIndices = nullptr);
			virtual void SubmitRenderCell(IRenderCell *pCell);

			virtual IShaderProgram *CreateShaderProgram();
			virtual void DestroyShaderProgram(IShaderProgram *pShaderProgram);

			virtual void Clear();
			virtual void Render();
			virtual void Render(IShaderProgram *pShaderProgram, uint materialId, uint bufferId, uint textureId);			
		private:			
			void TranslateWorldToCamera(const CMatrix4 &viewMat, Triangle &triangle);
			void TranslateCameraToScreen(const CMatrix4 &projMat, TriangleList &triList);
			bool BackCulling(const Triangle &triangle);										//±³ÃæÌÞ³ý			
			void VertexLightCalc(TriangleList &triList);
			void LoadMaterial();
		private:
			CSoftRenderDriver *m_pSoftRD;
			RenderQueueGroup m_renderQueueGroup;
			std::map<int, IBuffer *> m_mapCPUBuffer;
		};
	}
}

#endif