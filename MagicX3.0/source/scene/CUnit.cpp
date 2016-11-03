#include "scene/CUnit.h"
#include "CModel.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{

		CUnit::CUnit()
		{
			m_pMode = new CModel();
			m_pRenderable = RENDERER->CreateRenderable();
		}

		CUnit::~CUnit()
		{
			delete m_pMode;
			RENDERER->DestroyRenderable(m_pRenderable);
		}

		void CUnit::LoadModel(const char *filename)
		{
			if (m_pMode)
			{
				m_pMode->Load(filename);
			}

			//������Ⱦ������
		}

		void CUnit::Update(int delta)
		{
			//û�б��޳��������뵽��Ⱦ�б�
			if (true)
			{
				m_pRenderable->SumbitToRenderQueue();
			}
		}

	}
}