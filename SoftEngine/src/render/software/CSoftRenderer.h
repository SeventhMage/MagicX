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
				ubyte *vertices,						//��������				
				uint vertSize,							//�������ݳߴ�
				int count,								//��������
				VertexFormat format,					//�������Ը�ʽ
				ubyte *indices,							//��������
				uint indicesSize						//�������ݳߴ�
				) = 0;

			virtual void UpdateUniform(EUniformName name, ubyte *data, uint size);
			virtual void SubmitRenderCell(IRenderCell *pCell);

			virtual void Clear();
			virtual void Render();
			virtual void Render(uint materialId, uint bufferId, uint textureId);			
		private:			
			void TranslateWorldToCamera(TriangleList &triList);
			void TranslateCameraToScreen(TriangleList &triList);
			bool BackCulling(const Triangle &triangle);										//�����޳�
			bool TriangleSort(const Triangle &t1, const Triangle &t2);						//������������
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