#ifndef _SE_C_SOFT_RENDERER_H_
#define _SE_C_SOFT_RENDERER_H_

#include "render/IRenderer.h"
#include "render/IBuffer.h"
#include "render/SRenderMemory.h"
#include "render/IVertexArrayObject.h"
#include "render/IRenderQueue.h"
#include "base/CSingleton.h"
#include "math/CMatrix4.h"
#include "../STriangleMesh.h"
#include "CRasterizer.h"
#include "CSoftRenderDriver.h"
#include "render/SColor.h"


namespace se
{
	namespace render
	{
		class CSoftRenderer : public IRenderer, public base::CSingleton<CSoftRenderer>
		{
		public:
			typedef std::map<uint, IBuffer *> BufferMap;					//缓冲区map
			typedef std::map<uint, IVertexArrayObject *> VAOMap;			//顶点数组map
			typedef std::map<uint, IShaderProgram *> ShaderProgramMap;

			CSoftRenderer();
			virtual ~CSoftRenderer();
			virtual void Init();
			virtual IRenderDriver *GetRenderDriver() { return m_pSoftRD; }	
			virtual RenderDriverType GetRenderDriverType() { return m_pSoftRD->GetDriverType(); }
			virtual IRenderCell *CreateRenderCell(uint bufferId, uint materialId, uint textureId);
			virtual void DestroyRenderCell(IRenderCell *pCell);
			virtual uint CreateVAO();
			virtual void DestroyVAO(uint vaoId);
			virtual void VertexAttrPointer(uint vaoId, uint index, uint size, EDataType type, uint stride, uint offset);
			virtual uint CreateBuffer();
			virtual void DestroyBuffer(uint bufferId);			
			virtual void BufferData(uint bufferId, base::Vertices *pVertices, base::Indices *pIndices = nullptr);
			virtual void SubmitRenderCell(IRenderCell *pCell);

			virtual uint CreateShaderProgram();
			virtual void DestroyShaderProgram(uint shaderProgramId);
			virtual IShaderProgram *GetShaderProgram(uint shaderProgramId) const;

			virtual void Clear();
			virtual void Render();						

			virtual void UseShaderProgram(uint shaderProgramId);
			virtual void EnableVertexArrayObject(uint vaoId);
			virtual void BindBuffer(uint bufferId);
			virtual void BindTexture(uint textureId);

			virtual void DrawElements();
			virtual void DrawText(int iPosX, int iPoxY, const char *str, int length);
		private:			
			void TranslateWorldToCamera(const CMatrix4 &viewMat, Triangle &triangle);
			void TranslateCameraToScreen(const CMatrix4 &projMat, TriangleList &triList);
			bool BackCulling(const Triangle &triangle);										//背面剔除			
			void VertexLightCalc(const CVector3 &lightPos, const CMatrix4 &viewMat, TriangleList &triList);
			void LoadMaterial();
		private:
			CSoftRenderDriver *m_pSoftRD;
			CRasterizer *m_pRasterizer;			

			RenderQueueGroup m_renderQueueGroup;
			BufferMap m_mapCPUBuffer;
			VAOMap m_mapVAOs;		//存储于顶点级数对象中的缓冲区数据	
			ShaderProgramMap m_mapShaderProgram;


			//最终渲染时需要的对象
			uint m_shaderProgramId;
			uint m_vaoId;
			uint m_bufferId;
			uint m_textureId;
		};			
	}
}

#endif