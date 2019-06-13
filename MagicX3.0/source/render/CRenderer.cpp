#include "CRenderer.h"
#include "opengl/COpenGLDriver.h"
#include "CRenderList.h"
#include "CRenderable.h"
#include "CMaterial.h"
#include "CMaterialManager.h"
#include "renderphase/CRenderPhaseManager.h"

namespace mx
{
	namespace render
	{


		CRenderer::CRenderer(IRenderDriver *pRenderDriver)
			:m_pRenderDriver(pRenderDriver)
		{
			m_pMaterialMgr = new CMaterialManager();
			m_pRenderPhaseMgr = new CRenderPhaseManager();
			m_pScreenAlignedQuadManager = new CScreenAlignedQuadManager();
		}

		CRenderer::~CRenderer()
		{
			if (m_pRenderDriver)
				delete m_pRenderDriver;

			for (auto it = m_vecVertexArray.begin(); it != m_vecVertexArray.end(); ++it)
			{
				if (*it)
					delete (*it);
			}
			m_vecVertexArray.clear();

			SAFE_DEL(m_pMaterialMgr);
			SAFE_DEL(m_pRenderPhaseMgr);
			SAFE_DEL(m_pScreenAlignedQuadManager);
		}

		void CRenderer::Initialize(int width, int height)
		{
			m_pMaterialMgr->LoadMaterial("material/root.xml");
			m_pRenderPhaseMgr->LoadRenderPhase("renderphase/renderphase.xml");
			m_pRenderPhaseMgr->Initialize(this, width, height);
		}

		IRenderable * CRenderer::CreateRenderable(IRenderList *pRenderList)
		{
			return new CRenderable(pRenderList, this);
		}

		IRenderable * CRenderer::CreateRenderable(IRenderQueue * pQueue)
		{
			return new CRenderable(pQueue, this);
		}

		void CRenderer::DestroyRenderable(IRenderable *pRenderable)
		{
			if (pRenderable)
			{				
				pRenderable->RemoveFromRenderList();
				delete pRenderable;
			}
		}

		void CRenderer::AddVertexArrayObject(IVertexArrayObject *pObject)
		{
			auto it = std::find(m_vecVertexArray.begin(), m_vecVertexArray.end(), pObject);
			if (it == m_vecVertexArray.end())
			{
				m_vecVertexArray.push_back(pObject);
			}
		}

		void CRenderer::RemoveVertexArrayObject(IVertexArrayObject *pObject)
		{
			auto it = std::find(m_vecVertexArray.begin(), m_vecVertexArray.end(), pObject);
			if (it != m_vecVertexArray.end())
			{
				m_vecVertexArray.erase(it);
			}
		}


		void CRenderer::DestroyMaterial(IMaterial *pMaterial)
		{
			if (pMaterial)
				delete pMaterial;
		}

		void CRenderer::Render()
		{
			for (auto it = m_vecVertexArray.begin(); it != m_vecVertexArray.end(); ++it)
			{
				if (*it)
				{					
					(*it)->Render();
				}
			}
		}

		void CRenderer::EndRender()
		{
			for (auto it = m_vecVertexArray.begin(); it != m_vecVertexArray.end(); ++it)
			{
				if (*it)
				{
					(*it)->EndRender();
				}
			}
		}

		void CRenderer::ProcessRenderPhase() const
		{
			m_pRenderPhaseMgr->ProcessRenderPhase();
		}

		void CRenderer::SubmitScreenAlignedQuad() const
		{
			m_pScreenAlignedQuadManager->Render();
		}

	}
}