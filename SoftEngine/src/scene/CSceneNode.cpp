#include "CSceneNode.h"
#include "CScene.h"
#include "base/seDef.h"
#include <algorithm>


namespace se
{
	namespace scene
	{

		using namespace math;


		CSceneNode::CSceneNode(CScene *pScene)
			:m_pParentScene(pScene)
			, m_pEntity(nullptr)
			, m_pParentNode(nullptr)
			, m_bNeedUpdate(true)
			, m_bVisible(true)
			, m_relativeScale(1.f, 1.f, 1.f)
		{

		}


		CSceneNode::CSceneNode(const char *entityName, CScene *pScene)
			:m_pEntity(new CEntity(entityName, this))
			, m_pParentScene(pScene)
			, m_pParentNode(nullptr)
			, m_bNeedUpdate(true)
			, m_bVisible(true)
			, m_relativeScale(1.f, 1.f, 1.f)
		{

		}

		CSceneNode::~CSceneNode()
		{
			SAFE_DEL(m_pEntity);
			for (auto it = m_vecChildNode.begin(); it != m_vecChildNode.end(); ++it)
			{
				SAFE_DEL(*it);
			}
		}

		void CSceneNode::SetPosition(const CVector3 &position)
		{
			m_relativePosition = position;
			SetNeedUpdateMatrix(true);
		}

		const CVector3 & CSceneNode::GetPosition() const
		{
			return m_relativePosition;
		}

		void CSceneNode::SetRotation(const CVector3 &rotation)
		{
			m_relativeRotation = rotation;
			SetNeedUpdateMatrix(true);
		}

		const CVector3 & CSceneNode::GetRotation() const
		{
			return m_relativeRotation;
		}

		CVector3 CSceneNode::GetAbslutePosition() const
		{
			return m_absluateMatrix.GetTranslation();
		}

		void CSceneNode::SetScale(const CVector3 &scale)
		{
			m_relativeScale = scale;
			SetNeedUpdateMatrix(true);
		}

		const CVector3 & CSceneNode::GetScale() const
		{
			return m_relativeScale;
		}

		const CMatrix4 & CSceneNode::GetAbsluateMatrix() const
		{
			return m_absluateMatrix;
		}

		CMatrix4 CSceneNode::GetRelativeMatrix() const
		{
			return m_relativeMatrix;
		}

		void CSceneNode::SetVisible(bool visible)
		{
			m_bVisible = visible;
		}

		bool CSceneNode::IsVisible() const
		{
			return m_bVisible;
		}

		void CSceneNode::SetNeedUpdateMatrix(bool bNeed)
		{
			m_bNeedUpdate = bNeed;			
			for (auto it = m_vecChildNode.begin(); it != m_vecChildNode.end(); ++it)
			{
				(*it)->SetNeedUpdateMatrix(bNeed);
			}
		}

		void CSceneNode::UpdateRelateMatrix()
		{
			CMatrix4 mat;

			mat.SetTranslation(GetPosition());
			mat.SetRotationRadiansRH(GetRotation().x, GetRotation().y, GetRotation().z);
			if (m_relativeScale != CVector3(1.0f, 1.0f, 1.0f))
			{
				CMatrix4 smat;
				smat.SetScale(m_relativeScale);
				mat = mat * smat;
			}
			m_relativeMatrix = mat;
							
		}

		void CSceneNode::UpdateAbsluateMatrix()
		{
			if (m_pParentNode)
			{
				m_absluateMatrix = GetRelativeMatrix() * m_pParentNode->GetAbsluateMatrix();
			}
			else
			{
				m_absluateMatrix = GetRelativeMatrix();
			}					
		}

		void CSceneNode::Update(int delta)
		{			
			if (IsVisible())
			{
				if (m_bNeedUpdate)
				{
					UpdateRelateMatrix();
					UpdateAbsluateMatrix();
					m_bNeedUpdate = false;
				}

				for (auto it = m_vecChildNode.begin(); it != m_vecChildNode.end(); ++it)
				{
					(*it)->Update(delta);
				}

				if (m_pEntity)
				{
					m_pEntity->Update(delta);
				}
			}

		}

		void CSceneNode::AddChildNode(ISceneNode *pNode)
		{
			if (std::find(m_vecChildNode.begin(), m_vecChildNode.end(), pNode) == m_vecChildNode.end())
			{
				m_vecChildNode.push_back(pNode);
				pNode->SetParent(this);
			}
		}

		void CSceneNode::SetParent(ISceneNode *pNode)
		{
			if (pNode)
			{
				if (GetParent())
				{
					GetParent()->RemoveChildNode(this);
				}
				m_pParentNode = pNode;
			}
		}

		void CSceneNode::RemoveChildNode(ISceneNode *pNode)
		{
			auto it = std::find(m_vecChildNode.begin(), m_vecChildNode.end(), pNode);
			if (it != m_vecChildNode.end())
			{
				m_vecChildNode.erase(it);
			}
		}

	}
}