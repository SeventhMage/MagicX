#ifndef _H_SCENE_NODE_H_INC_
#define _H_SCENE_NODE_H_INC_

#include <list>
#include "mxType.h"
#include "core/CMatrix4.h"
#include "core/CVector3.h"

namespace mx
{
	namespace scene
	{
		using core::CVector3;
		using core::CMatrix4;
		class IScene;
		class ISceneNode
		{
		public:
			ISceneNode()
				:m_pNodeParent(NULL)
				, m_pSceneParent(NULL)
				, m_bVisible(true)
				, m_bActive(true)
			{
			};
			virtual ~ISceneNode(){};
			
			virtual void UpdateImp(int elapsedTime) = 0;
			virtual void RenderImp() = 0;

 			void Render()
 			{
 				RenderImp();
 				std::list<ISceneNode *>::iterator it = m_listChild.begin();
 				for (; it != m_listChild.end(); ++it)
 				{
 					(*it)->Render();
 				}				
 			}

			void Update(uint elapsedTime)
			{
				UpdateImp(elapsedTime);
				std::list<ISceneNode *>::iterator it = m_listChild.begin();
				for (; it != m_listChild.end(); ++it)
				{
					(*it)->Update(elapsedTime);
				}
			}



			void SetParent(ISceneNode *parent)
			{
				if (parent)
				{
					Remove();
					parent->AddChild(this);
					m_pNodeParent = parent;
				}
			}
			void AddChild(ISceneNode *child)
			{
				m_listChild.push_back(child);
			}

			void SetScene(IScene *pScene)
			{
				m_pSceneParent = pScene;
			}

			void Remove()
			{
				if (m_pNodeParent)
					m_pNodeParent->RemoveChild(this);
			}
			void RemoveChild(ISceneNode *child)
			{
				m_listChild.remove(child);
			}

			void RemoveAll()
			{
				m_listChild.clear();
			}

			void SetPosition(const CVector3 &position)
			{
				m_relativePosition = position;
			}

			const CVector3 &GetPosition() const
			{
				return m_relativePosition;
			}
			
			const CVector3 &GetRotation() const
			{
				return m_relativeRotation;
			}

			CVector3 GetAbslutePosition() const
			{
				return m_absluateTransformation.GetTranslation();
			}

			void SetScale(const CVector3 &scale)
			{
				m_relativeScale = scale;
			}

			const CVector3 &GetScale() const
			{
				return m_relativeScale;
			}

			const CMatrix4 &GetAbsluateTransformation() const
			{
				return m_absluateTransformation;
			}
			CMatrix4 GetRelativeTransformation() const
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

			void SetVisible(bool visible)
			{
				m_bVisible = visible;
			}

			bool IsVisible()const
			{
				return m_bVisible;
			}

			//3D检测后，可见为true, 不可见为false
			void SetActive(bool bActive) { m_bActive = bActive; }
			bool IsActive() const { return m_bActive; }		

			const std::string &GetName() const
			{
				return m_name;
			}

			void UpdateAbsluateTransformation()
			{
				if (m_pNodeParent)
				{
					m_absluateTransformation = m_pNodeParent->GetAbsluateTransformation() * GetRelativeTransformation();
				}
				else
					m_absluateTransformation = GetRelativeTransformation();
			}

		protected:
			ISceneNode *m_pNodeParent;
			std::list<ISceneNode *> m_listChild;
			IScene *m_pSceneParent;

			CMatrix4 m_absluateTransformation;
			CVector3 m_relativePosition;
			CVector3 m_relativeRotation;
			CVector3 m_relativeScale;						
			std::string m_name;
			bool m_bVisible;
			bool m_bActive;
		};
	}
}

#endif // !_H_SCENE_NODE_H_INC_
