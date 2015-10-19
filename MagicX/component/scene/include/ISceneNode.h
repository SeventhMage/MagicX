#ifndef _H_SCENE_NODE_H_INC_
#define _H_SCENE_NODE_H_INC_

#include <list>
#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		class ISceneNode
		{
		public:
			ISceneNode()
				:m_pNodeParent(NULL)
				, m_bVisible(true)
			{
			};
			virtual ~ISceneNode(){};
			
			virtual void UpdateImp(uint elapsedTime) = 0;
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
				return m_absluateTransformation.getTranslation();
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

				mat.setTranslation(GetPosition());
				mat.setTranslation(GetRotation());
				if (m_relativeScale != CVector3(1.0f, 1.0f, 1.0f))
				{
					CMatrix4 smat;
					smat.setScale(m_relativeScale);
					mat *= smat;
				}
				return mat;
			}

			void SetVisible(bool visible)
			{
				m_bVisible = visible;
			}

			bool GetVisible()const
			{
				return m_bVisible;
			}

			const CString &GetName() const
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

			CMatrix4 m_absluateTransformation;
			CVector3 m_relativePosition;
			CVector3 m_relativeRotation;
			CVector3 m_relativeScale;						
			CString m_name;
			bool m_bVisible;
		};
	}
}

#endif // !_H_SCENE_NODE_H_INC_
