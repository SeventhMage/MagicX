#include "scene/CSceneNode.h"

namespace mx
{
	namespace scene
	{

		CSceneNode::CSceneNode()	
			: m_bVisible(true)
			, m_bActive(true)
			, m_bNeedUpdate(true)
			, m_pNodeParent(nullptr)
			, m_relativeScale(1.0f, 1.0f, 1.0f)
		{

		}

		CSceneNode::~CSceneNode()
		{

		}

		void CSceneNode::UpdateImp(int delta)
		{

		}

		void CSceneNode::Update(uint delta)
		{
			UpdateAbsluateTransformation();
			UpdateImp(delta);
			std::list<ISceneNode *>::iterator it = m_listChild.begin();
			for (; it != m_listChild.end(); ++it)
			{
				(*it)->Update(delta);
			}
		}

		void CSceneNode::SetParent(ISceneNode *parent)
		{
			if (parent)
			{
				m_pNodeParent = parent;
			}
		}

		void CSceneNode::AddChild(ISceneNode *child)
		{
			if (child)
			{			
				child->SetParent(this);
				m_listChild.push_back(child);
			}			
		}

		void CSceneNode::Remove()
		{
			if (m_pNodeParent)
				m_pNodeParent->RemoveChild(this);
		}

		void CSceneNode::RemoveChild(ISceneNode *child)
		{
			m_listChild.remove(child);
		}

		void CSceneNode::RemoveAll()
		{
			m_listChild.clear();
		}

		void CSceneNode::SetPosition(const CVector3 &position)
		{
			m_relativePosition = position;
			SetNeedUpdateTransformation(true);
		}

		const CVector3 & CSceneNode::GetPosition() const
		{
			return m_relativePosition;
		}

		void CSceneNode::SetRotation(const CVector3 &rotation)
		{
			m_relativeRotation = rotation;
			SetNeedUpdateTransformation(true);
		}

		const CVector3 & CSceneNode::GetRotation() const
		{
			return m_relativeRotation;
		}

		mx::scene::CVector3 CSceneNode::GetAbslutePosition() const
		{
			return m_absluateTransformation.GetTranslation();
		}

		void CSceneNode::SetScale(const CVector3 &scale)
		{
			m_relativeScale = scale;
			SetNeedUpdateTransformation(true);
		}

		const CVector3 & CSceneNode::GetScale() const
		{
			return m_relativeScale;
		}

		const CMatrix4 & CSceneNode::GetAbsluateTransformation() const
		{
			return m_absluateTransformation;
		}

		mx::scene::CMatrix4 CSceneNode::GetRelativeTransformation() const
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
			return mat;
		}

		void CSceneNode::SetVisible(bool visible)
		{
			m_bVisible = visible;
		}

		bool CSceneNode::IsVisible() const
		{
			return m_bVisible;
		}

		void CSceneNode::SetActive(bool bActive)
		{
			m_bActive = bActive;
		}

		bool CSceneNode::IsActive() const
		{
			return m_bActive;
		}

		const std::string & CSceneNode::GetName() const
		{
			return m_name;
		}

		void CSceneNode::UpdateAbsluateTransformation()
		{
			if (m_bNeedUpdate)
			{				
				if (m_pNodeParent)
				{					
					m_absluateTransformation = GetRelativeTransformation() * m_pNodeParent->GetAbsluateTransformation();
				}
				else
				{
					m_absluateTransformation = GetRelativeTransformation();
				}

				m_bNeedUpdate = false;
			}
		}

		void CSceneNode::SetNeedUpdateTransformation(bool bNeed)
		{
			m_bNeedUpdate = bNeed;
			for (auto it = m_listChild.begin(); it != m_listChild.end(); ++it)
			{
				(*it)->SetNeedUpdateTransformation(bNeed);
			}
		}

	}
}